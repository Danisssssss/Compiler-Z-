Новый язык программирования Z++ имеет возможность работы лишь с одним целочисленным регистром А, а также выполнять только две команды- ADD (сложение) и MUL (умножение).
Формат этих команд:
  ADD X Y;	
  MUL X Y;
где: X, Y – любая десятичная цифра, либо регистр А.
Разделителем операндов X и Y является символ “пробел”, а разделителем команд (строк) является символ “точка с запятой”.	
Результат выполнения команды всегда попадает в регистр А.
В начале работы программы значение регистра А равно нулю.

Написать программу-интерпретатор на С++, выполняющую фрагмент программы, написанной на Z++:
  MUL 2 9;
  MUL A 3;
  ADD 8 A;  
Вывести содержимое регистра А после выполнения каждой строки

Примечание.
1. Исходный текст на Z++ должен быть записан в отдельном файле и прочитан с помощью команд работы с файлами.
2. Предусмотреть проверку синтаксиса команды (мнемоника, операнды, разделители).
