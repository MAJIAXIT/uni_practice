### Задание 

Структура данных – очередь.

Уровень сложности – средний. 

Написать на языке С++ программу, решающую поставленную в вариативной части задачу, используя указанную там же структуру данных. 	Выполнение задания осуществляется в два этапа. 	На первом этапе требуется реализовать необходимую структуру данных с помощью одной структуры хранения (векторной или связной), реализацию оформить в виде класса. Методы класса должны выполнять только основные и дополнительные операции, допустимые над элементами описываемой СД (перечислены ниже). Никаких других операций в классе быть не должно. 

На втором этапе требуется использовать объекты созданного класса при решении поставленной задачи. 

Структура данных – очередь. 

Фирма по хранению и сбыту бытовых инструментов получает грузы с оборудованием по различным ценам и продает их затем с 20%-ной надбавкой, причем товары, полученные ранее, продаются в первую очередь. Напишите программу, считывающую записи о торговых операциях двух типов: операции по закупке и операции по продаже. Запись о продаже содержит префикс “S” и количество товара. Запись о закупке содержит префикс “R”, количество товара и стоимость одного изделия. После считывания записи о закупке напечатайте ее с указанием стоимости всей партии. После считывания записи об операции продажи напечатайте, сколько изделий было продано, цену одного изделия в каждой продаваемой партии, стоимость каждой партии и суммарную стоимость всей сделки. Например, если фирмой были проданы 200 единиц оборудования, в которые входили 50 единиц с закупочной ценой 1.25$ и 150 единиц с закупочной ценой 1.1$, то напечатаны должны быть три строки: 

50 штук по 1.50$ каждый на сумму 75.00$

150 штук по 1.32$ каждый на сумму 	198.00$

Всего продано на сумму 273.00$ 

Если на складе отсутствует требуемое в заказе число изделий, то продайте все имеющиеся, а затем напечатайте сообщение об отсутствии остальной части изделий на складе. 