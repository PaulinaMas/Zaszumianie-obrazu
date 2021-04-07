.data
stopien dq ? ;stopien zaszumienia

.code
MyProc1 proc 

mov r12, qword ptr [rsp+40] ;pierwszy argument ze stosu, poziom zaszumienia
shl r12,25 ;przesuniecie zeby zosta³ sam argument do czytania
shr r12,25
mov stopien, r12
mov r12, qword ptr [rsp+48] ;pobranie konca podtablicy
shl r12,30
shr r12,30
mov r11, r12 ;tu w r11 koniec podtablicy
mov r10, rdx ;tu k, czyli iterator petli zewnetrznej

push rbx ;trzeba zachowaæ rbx, inaczej nie dzia³a w release

L1:
mov r12,rcx; wysokosc tablicy
mov rdi,[r8 + rdx*8] ;wskaznik na podtablice
mov rsi,[r9 + rdx*8] ;wskaznik na podtablice losowa
L2:
movd xmm0,dword ptr[rdi];odczytanie piksela z bitmapy1
pmovzxbd xmm0, dword ptr[rdi];rozdzielenie sk³adowych piksela z b1 ¿eby odczytac tylko jeden kolor
movd xmm1,dword ptr[rsi];odczytanie piksela z bitmapy2
pmovzxbd xmm1, dword ptr[rsi];rozdzielenie sk³adowych piksela z b2
 ;bedziemy rozdzielac na poszczegolne kolorki
shufps xmm0, xmm0, 4Eh ;przesuwamy ¿eby tylko jeden kolor zostal
movd rbx, xmm0	
shufps xmm1, xmm1, 4Eh ;to samo przesuniecie ale dla losowej 
movd rax, xmm1
xor rbx,rax ;xor i mamy nowy kolor

mov r13, rbx ;czerwony do r10

shufps xmm0, xmm0, 93h
pmovzxbd xmm2,xmm0; jeszcze jedno rozdzielenie
movd rbx, xmm2		
shufps xmm1, xmm1, 93h
pmovzxbd xmm3,xmm1
movd rax, xmm3
xor rbx,rax
mov r14, rbx ;zielony do r14

shufps xmm0, xmm0, 93h
pmovzxbd xmm2,xmm0 ;ostatnie rozdzielenie
movd rbx, xmm2	
shufps xmm1, xmm1, 93h
pmovzxbd xmm3,xmm1
movd rax, xmm3
xor rbx,rax
mov r15, rbx ;niebieski do r15

; tu robienie pseudolosowej liczby
movd xmm10, rcx
movd xmm11, rdx
push r13 ;zachowanie czerwonego koloru, bo dzia³ania na r13
add r13, r14;losowanie
imul r13, r15;losowanie
xor rax,rax
mov rax, r13 ;do raxa
xor rdx, rdx ;czyscimy rdx
mov  ecx,  100         
cqo         ; w rcx mam czesc cala ale nie potrzebuje jej
idiv   rcx ; teraz w rdx mam reszte 
movd rcx, xmm11 ;przywracamy rcx 
pop r13

cmp rdx, stopien ;porównanie wylosowanej liczby ze stopniem
movd rdx, xmm10
ja x ;je¿eli wieksza ni¿ stopien zostawiamy piksel w spokoju 
movd xmm4, r15
mov rbx,r14
shl rbx,8 ;przesuniecia ¿eby stworzyæ oryginalnie wczytana strukturê piksela
movd xmm5, rbx
addsd xmm4,xmm5
mov rbx,r13
shl rbx,16
movd xmm5, rbx
addss xmm4,xmm5
movd dword ptr[rdi], xmm4;zapisanie piksela
x:
add rdi,4 ;kolejny piksel
add rsi,4
dec r12
jnz L2 ;petla wewnetrzna, chodzimy po wysokosci

add r8,8 ;kolejny wiersz
add r9,8
inc r10
cmp r10,r11 ;patrzymy czy ju¿ koniec podtablicy
jl L1 ;petla zewnetrzna 

pop rbx ;przywrocenie rbx na sam koniec

ret

MyProc1 endp
end
