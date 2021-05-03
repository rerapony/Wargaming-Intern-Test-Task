#### Решение

##### Task 1

Изначальное решение: 
Pros: по коду сразу понятно, что происходит; 
Cons: может быть медленнее на некоторых (старых версиях) компиляторов, чем решение с битовой логической операцией &. Однако оптимизация решает.

Решение с использованием битовой операции &: 
Pros: должно быть быстрее, т.к. проверяется только последний бит числа и логическая операция работает быстрее взятия модуля; 
Cons: менее понятно, что происходит.

Современные компиляторы достаточно хорошо оптимизируют код, чтобы решение с модулем не проигрывало решению с битовой операцией, поэтому существенных различий нет.

##### Task 2

Рассмотрим два варианта:

- очередь на базе односвязного списка:
Pros: добавление О(1); удаление О(1); динамический размер - не выделяем память для неиспользованных элементов
Cons: для каждого элемента храним по ссылке на предыдущий - экстра память; обращение по индексу - O(n)
- на базе статического массива:
Pros: добавление О(1); доступ к элементу за O(1); не тратим память на хранение указателя
Cons: удаление О(n)); очередь жестко ограничена по размеру. Если количество фактически добавленных элементов < capacity, то мы зря выделили память и не используем ее.


##### Task 3

Рассмотрим известные алгоритмы сортировки:

Сортировки, основанные на сравнениях:

- QuickSort - O(N^2) в худшем случае (отсортированный массив (в прямом и обратном порядках))

- MergeSort - O(logN) сложость во всех случаях, но занимает много места (O(n)). 

- HeapSort дает O(logN) и занимает всего O(1) памяти, но MergeSort имеет меньшую константу (быстрее).
 
- Insertion Sort дает O(n) для отсортированного массива, но O(n^2)  - в худшем случае (для отсортированного в обратном порядке).

Сортировки, не использующие сравнения:

- BucketSort - O(n^2) в худшем случае (разряженный массив)

- RadixSort - O(w*n), где w - количество разрядов в числе.

- CountingSort - O (n+k),  где k - максимальное число из диапазона, которому принадлежат все элементы массива.

Если мы знаем природу элементов, поступающих на вход, то сортировки, не основанные на сравнении, являются хорошим вариантом, т.к. предполагают сложность, близкую к линейной. Однако BucketSort не дает никакого выиграша в случае разряженного массива, RadixSort - проигрывает если количеством разрядов в числе >= log(количество всех чисел), CountingSort - может дать очень плохой результат, если диапазон числе > количества элементов.

Т.к. мы ничего не знаем про массив на входе, то не следует использовать сортировки, не основанные на сравнениях, по приведенным выше аргументам. Из сортировок, основанных на сравнениях, QuickSort в среднем дает лучший результат, но MergeSort - в худшем. В задаче подразумевается, что мы должны учесть худший результат, поэтому выбираем MergeSort.