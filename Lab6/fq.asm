.386 
.model flat, C 
.code 

poisk proc public, NumRanDat:dword, arr:ptr dword, RG:ptr dword, kol:ptr dword, NInt:dword 
push ebx ;сохранение текущего значения регистра ebx 
push esi ;сохранение текущего значения регистра esi 
push eax ;сохранение текущего значения регистра eax 
mov ecx, NumRanDat ;помещение в регистр ecx значения количества псевдослучайных чисел в массиве 
mov esi,0 ;помещение в регистр esi значение 0, данный регистр будет использоваться в качестве счетчика 

Chislo: ;метка для получения числа из массива псевдослучайных чисел 
mov eax,arr ;помещение в регистр eax начала массва псевдослучайных чисел 
mov eax,[eax+esi*4] ;обращение к ячейке массива псевдослучайных чисел, с использованием счетчика esi 
mov edx,-1 ;помещение в регистр edx знаяение -1 

Interval: 
inc edx ;увеличение на 1 значения регистра, обнуление регистра edx 
mov ebx,RG ;помещение в регистр ebx начала массива границ 
mov ebx,[ebx+edx*4] ;обращение к ячейке массива границ с индексом edx 
cmp eax,ebx ;сравнение псевдослучайного числа с границей 
jg Interval ;переход если больше 

mov ebx,kol ;помещение в регистр ebx начала массива повторений 
mov eax,[ebx+edx*4] ;помещение в регистр значения ячейки с индексом edx 
inc eax ;увеличение на 1 значения 
mov [ebx+edx*4],eax ;помещние значения в ячейку с индексом edx 
inc esi ;увеличение счетчика 
Loop Chislo 

pop eax ;возвращение значения eax 
pop esi ;возвращение значения esi 
pop ebx ;возвращение значения ebx 
ret 
poisk endp 
end 
