.type start, %function

.word stack_top /* Вот это вершина стека */
.word start         /* А здесь инициализируем PC */

.global start
start:
	ldr r1, =c_entry
	bx r1
