AStack SEGMENT STACK
	DW 512 DUP(?)
AStack ENDS


DATA SEGMENT
	String db '000000000$'; строка для перевода числа из ax в строковый вид
	str_imagine db '-1267$'; строка для загрузки числа в ax
	Direct_info db 'Число после преобразования в строку с учетом знака', 10, 13, '$'
	Reverse_info db 'Строка для обратной функции $'
	ax_out db 'ax:$'
	Line_break db 13, 10, '$'
DATA ENDS


CODE SEGMENT
	ASSUME CS:CODE, DS:DATA, SS:AStack
	;число храниться в ax, строку необходимо записать в string

	PrintMessage PROC NEAR
		mov ah, 09h
		int 21h
		ret
	PrintMessage ENDP

	to_str PROC NEAR
		start:
			push bx
			xor si, si ; si - текущий редактируемый символ в строке
			;mov eax, [num]          ;заносим число в регистр для дальнейшего деления
			test ax, ax           ;проверка знака числа в AX
			jns unum_to_str         ;переход, если число без знака или равно нулю
			mov bl, '-'
			mov String[si], bl      ;добавление знака в начало строки
			inc si
			inc di
			neg ax             ;инвертирование двоичного числа в AX 

		;Преобразование беззнакового числа
		unum_to_str:
		    xor cx, cx        ;обнуление счетчика - необходим для запоминания кол-ва итераций
		    mov bx, 10     ;помещаем в регистр BX делитель
		    cycle1:
		    xor dx, dx        ;обнуление старшей части двойного слова (остатка)
		    div bx         ;деление (DX:AX)/EBX, остаток в DX, частное в AX
		    add dx, 30h        ;Преобразование остатка в код символа
		    push dx        ;сохраняем остаток в стеке
		    inc cx         ;увеличиваем счетчик цикла (для второго цикла)  
		    test ax, ax       ;проверка EAX
		    jnz cycle1      ;переход к началу цикла, если частное не ноль

		cycle2:
		    pop dx         ;восстановление символа из стека
		    mov String[si], dl      ;сохранение символа в строку
		    inc si ; увеличиваем счетчик
		    loop cycle2     ;цикл продолжается, пока CX>0
		 mov String[si], '$'
		;Восстановление из стека
		pop bx
		ret
	to_str ENDP
 
	;-------------mul dx on bx and bx on 10-------------;
	mul_dx_bx PROC NEAR
		push cx ; сохранение cx
		mov cx, bx
		cmp cx, 1; dx * 1
		je mul_bx_10
		dec cx
		mov di, dx
		m1:
			add dx, di
			loop m1
		mul_bx_10:
			mov cx, 9; необходимо сложить bx с самим собой 10 раз <-> умножение на 10
			mov di, bx
			m2:
				add bx, di
				loop m2
			pop cx; восстановление cx
			ret
	mul_dx_bx ENDP

	to_num PROC NEAR
		xor ax, ax ; обнуление ax
		xor si, si; обнуление счетчика по строке
		xor cx, cx
		mov bx, 1h; стартовый множитель
		cmp str_imagine[si], '-'
		je inc_si
		push_to_stack:
			cmp str_imagine[si], '$'
			je built_num
			xor dx, dx
			mov dl, str_imagine[si]
			sub dl, 30h; преобразование в число
			push dx
			inc si;
			inc cx;
			jmp push_to_stack
		built_num:
			pop dx
			call mul_dx_bx
			add ax, dx
			loop built_num
			jmp end1
		inc_si:
			inc si
			jmp push_to_stack
		end1:
			cmp str_imagine[0], '-'
			jne end2
			neg ax
		end2:
			ret
	to_num ENDP

	Main PROC FAR
		push ds
		sub ax, ax
		push ax
		mov ax, DATA
		mov ds, ax
		;--------------Задание ax---------------;
		mov ax, 11h
		neg ax; 

		;--------------Прямое преобразование из заданного выше ax в строку String----------;
		call to_str
		mov dx, offset Direct_info
		call PrintMessage
		mov dx, offset String
		call PrintMessage
		mov dx, offset Line_break
		call PrintMessage

		;--------------Обратное преобразование из строкого представления ax в str_imagine----------;
		call to_num
		call to_str
		mov dx, offset Reverse_info
		call PrintMessage
		mov dx, offset str_imagine
		call PrintMessage 
		mov dx, offset Line_break
		call PrintMessage
		mov dx, offset ax_out
		call PrintMessage
		mov dx, offset String
		call PrintMessage
		ret
	Main endp
CODE ENDS
END Main
