# 01. Регистры общего назначения

## Регистры общего назначения

___Регистры___ — специальные ячейки памяти, находящиеся физически внутри процессора, доступ к которым осуществляется не по адресам, а по именам. Поэтому, работают очень быстро.

Существуют регистры, которые могут использоваться без ограничений, для любых целей — регистры общего назначения.

___В 8086 регистры 16 битные.___

При использовании регистров общего назначения, можно обратится к каждым 8 битам (байту) по-отдельности, используя вместо *X - *H или *L (например, для AX: AH и AL)

## AX (аккумулятор)

Регистр часто используется для хранения результата действий, выполняемых над двумя операндами. Например, используется при MUL и DIV (умножение и деление)

Верхние 8 бит (1 байт) — AH

Нижниие 8 бит (1 байт) — AL

## BX (база)

Используется для адресации по базе.

Верхние 8 бит (1 байт) — BH

Нижние 8 бит (1 байт) — BL

## CX (счётчик)

Используется как счётчик в циклах и строковых операциях.

Верхние 8 бит (1 байт) — CH

Нижние 8 бит (1 байт) — CL

## DX (регистр данных)

Если при выполнении действий над двумя операндами, реузльтат не помещается в AX, регистр DX получает старшую часть результата.

Верхние 8 бит (1 байт) — DH

Нижние 8 бит (1 байт) — DL

Этот регистр получает старшую часть данных,

## SI (индекс источника) и DI (индекс приемника)

Ещё есть два этих регистра, они называются индексными, то есть используются для индексации в массивах / матрицах и т.д. (другие регистры (кроме BX и BP) не будут там работать (на 8086)).

Могут использоваться в большинстве команд, как регистры общего назначения.

___В этих регистрах нельзя обратится к каждому из байтов по-отдельности___

# 02. Сегментные регистры. Адресация в реальном режиме. Понятие сегментной части адреса и смещения.

## Сегментные регистры

■ Сегмент кода (CS)

■ Сегменты данных (DS, ES, FS, GS)

■ Сегмент стека (SS)

Каждый регистр содержит адрес для разных сегментов программы, с помощью них и происходит доступ к этим сегментам.

Мы знаем что регистр IP "указывает" на следующую команду, мы также знаем что регистры у нас размером в 16 бит, таким образом, используя один регистр программист имеет доступ только к 2^16 адресам, это примерно 64 кБ. Это достаточно мало, поэтому адресация в 8086 по 2^20 адресам, то есть примерно 1 МБ памяти. Для этого используют адрес начала сегмента и смещение. Сегментные регистры как раз хранят адрес. Реальный адрес высчитывается так: сегментная_часть × 16 + смещение. (умножение на 16 = сдвиг на четыре бита влево)

При такой адресации адреса 0400h:0001h и 0000h:4001h будут ссылаться на одну и ту же ячейку памяти, так как 400h × 16 + 1 = 0 × 16 + 4001h.

# 03. Регистры работы со стеком.

## Стек

___Стек___ - структура данных, работающая по принципу LIFO (last in, first out) - последним пришёл, первым вышел.

___Сегмент стека___ - область памяти программы, используемая её подпрограммами, а также (вынужденно) обработчиками прерываний.

___SP___ - указатель на вершину стека, ___BP___ - указатель на начало стека. BP используется в подпрограмме для сохранения "начального" значения ___SP___, адресации параметров и локальных переменных.

В ___x86___ стек растёт вниз, в сторону уменьшения адресов. При запуске программы ___SP___ указывает на конец сегмента.

## Команды непосредственной работы со стеком

### PUSH <источник>

Помещает данные в стек. Уменьшает ___SP___ на размер источника и записывает значение по адресу ___SS:SP___.

### POP <приемник>

Считывает данные из стека. Считывает значение с адреса ___SS:SP___ и увеличивает ___SP___.

### PUSHA

Помещает в стек регистры ___AX___, ___CX___, ___DX___, ___BX___, ___SP___, ___BP___, ___SI___, ___DI___.

### POPA

Загружает регистры из стека (SP игнорируется).

## Вызов процедуры и возврат из процедуры

### CALL <операнд>

Сохраняет адрес следующей команды в стеке (уменьшает ___SP___ и записывает по его адресу либо IP либо ___CS:IP___, в зависимости от размера аргумента. Передает управление на значение аргумента.

### RET/RETN/RETF <число>

Загружает из стека адрес возврата, увеличивает ___SP___. Если указан операнд, его значение будет дополнительно прибавлено к ___SP___ для очистки стека от параметров.

# 04. Структура программы. Сегменты.

## Структура программы

Любая программа состоит из сегментов

/// ! Виды сегментов:

Сегмент кода

Сегмент данных

Сегмент стека

/// ! Описание сегмента в исходном коде:

имя __SEGMENT READONLY__ выравнивание тип разряд 'класс'

…

имя __ENDS__

Структура программы на ассемблере (Зубков С. В., Assembler для DOS, Windows, …, глава 3):

* Модули (файлы исходного кода)
* Сегменты (описание блоков памяти)
* Составляющие программного кода:
   - команды процессора
   - инструкции описания структуры, выделения памяти, макроопределения
* Формат строки программы:
   - метка команда/директива операнды ; комментарий

## Директива SEGMENT

Каждая программа, написанная на любом языке программирования, состоит из одного или нескольких сегментов. Обычно область памяти, в которой находятся команды, называют сегментом кода, область памяти с данными - сегментом данных и область памяти, отведённую под стек, - сегментом стека.

Выравнивание:

* BYTE

* WORD

* DWORD

* PARA (по умолчанию)

* PAGE

Тип:

* PUBLIC - заставляет компоновщик соединить все сегменты с одинаковым именем. Новый объединенный сегмент будет целым и непрерывным. Все адреса (смещения) объектов, а это могут быть, в зависимости от типа сегмента, команды или данные, будут вычисляться относительно начала этого нового сегмента;

* STACK - определение сегмента стека. Заставляет компоновщик соединить все одноименные сегменты и вычислять адреса в этих сегментах относительно регистра SS. Комбинированный тип STACK (стек) аналогичен комбинированному типу PUBLIC, за исключением того, что регистр SS является стандартным сегментным регистром для сегментов стека. Регистр SP устанавливается на конец объединенного сегмента стека. Если не указано ни одного сегмента стека, компоновщик выдаст предупреждение, что стековый сегмент не найден. Если сегмент стека создан, а комбинированный тип STACK не используется, программист должен явно загрузить в регистр SS адрес сегмента (подобно тому, как это делается для регистра DS);

* COMMON - располагает все сегменты с одним и тем же именем по одному адресу. Все сегменты с данным именем будут перекрываться и совместно использовать память. Размер полученного в результате сегмента будет равен размеру самого большого сегмента;

* AT - располагает сегмент по абсолютному адресу параграфа (параграф — объем памяти, кратный 16, поэтому последняя шестнадцатеричная цифра адреса параграфа равна 0). Абсолютный адрес параграфа задается выражением хххx. Компоновщик располагает сегмент по заданному адресу памяти (это можно использовать, например, для доступа к видеопамяти или области ПЗУ), учитывая атрибут комбинирования. Физически это означает, что сегмент при загрузке в память будет расположен, начиная с этого абсолютного адреса параграфа, но для доступа к нему в соответствующий сегментный регистр должно быть загружено заданное в атрибуте значение. Все метки и адреса в определенном таким образом сегменте отсчитываются относительно заданного абсолютного адреса;

* PRIVATE (по умолчанию) - сегмент не будет объединяться с другими сегментами с тем же именем вне данного модуля.

Класс:

Это любая метка, взятая в одинарные кавычки. Сегменты одного класса расположатся в памяти друг за другом.

## Директива ASSUME

__ASSUME__ _регистр_ : _имя сегмента_

* Не является командой
* Нужна для контроля компилятором правильности обращения к переменным

## Модель памяти

.model _модель, язык, модификатор_

* TINY - один сегмент на всё
* SMALL - код в одном сегменте, данные и стек - в другом
* COMPACT - допустимо несколько сегментов данных
* MEDIUM - код в нескольких сегментах, данные - в одном
* LARGE, HUGE
* Язык - C, PASCAL, BASIC, SYSCALL, STDCALL. Для связывания с ЯВУ и вызова подпрограмм.
* Модификатор - NEARSTACK/FARSTACK
* Определение модели позволяет использовать сокращённые формы директив определения сегментов.

## Конец программы и точка входа

...

END start

* start - имя метки, объявленной в сегменте кода и указывающее на команду, с которой начнётся исполнение программы.
* Если в программе несколько модулей, только один может содержать начальный адрес.

# 05. Прерывание 21h. Примеры ввода вывода.

## Прерывание 21h

* Аналог системного вызова в современных ОС.
* Используется наподобие вызова подпрограммы.
* Номер функции передается через АН.

<!DOCTYPE html>

функция | назначение | вход | выход
-- | -- | -- | --
02 | Вывод символа в stdout | DL = ASCII-код символа | -
09 | Вывод строки в stdout | DS:DX - адрес строки, заканчивающейся символом $ | -
01 | Считать символ из stdin с эхом | - | AL – ASCII-код символа
06 | Считать символ без эха, без ожидания, без проверки на Ctrl+Break | DL=FF | AL – ASCII-код символа
07 | Считать символ без эха, с ожиданием и без проверки на Ctrl+Break | - | AL – ASCII-код символа
08 | Считать символ без эха | - | AL – ASCII-код символа
10 (0Ah) | Считать строку с stdin в буфер | DS:DX - адрес буфера | Введённая строка помещается в буфер
0Bh | Проверка состояния клавиатуры - AL=0, если клавиша не была нажата, и FF, если была |   |  
OCh | Очистить буфер и считать символ | AL=01, 06, 07, 08, 0Ah | -

Еще одним важным случаем, когда нам требуется прерывание DOS - завершение программы. Чтобы ассемблер перестал читать подряд строки кода нам требуется положить в ah код DOS завершения программы (04Ch) и вызвать прерывание. Код завершения программы (ошибка или нет) кладется и берется из al.

```assembler
; завершить программу с кодом 3
mov al, 03h
mov ah, 04Ch ; оно же 4Сh
int 21h
```
## Примеры
```assembler
; ввод символа (результат сохраняется в в al)
mov ah, 01h
int 21h

----------------

; вывод символа на экран (содержащегося в dl)
mov dl, 'x'
mov ah, 02h
int 21h
```

# 06. Стек. Назначение, примеры использования.

## Стек. Назначение, примеры использования.

Стек работает по правилу LIFO / FILO (последним пришёл, последним вышел)

Сегмент стека — область памяти программы, используемая её подпрограммами, а также (вынужденно) обработчиками прерываний.

Используется для временного хранения переменных, передачи параметров для подпрограм, адрес возврата при вызове процедур и прерываний.

Регистр SP — указывает на вершину стека

В x86 стек "растёт вниз", в сторону уменьшения адресов (от максимально возможно адреса). При запуске программы SP указывает на конец сегмента.

## BP (Base Pointer)

Используется в подпрограмме для сохранения "начального" значения SP.

Так же, используется для адресации параметров и локальных переменых.

При вызове подпрограммы параметры кладут на стек, а в BP кладут текущее значение SP. Если программа использует стек для хранения локальных переменных, SP изменится и таким образом можно будет считывать переменные напрямую из стека (их смещения запишутся как BP + номер параметра)

<img width="720" alt="Снимок экрана 2023-03-27 в 14 28 53" src="https://user-images.githubusercontent.com/57632162/227929031-19516be8-4013-4304-8acc-6101ea56ad12.png">

## Команды работы со стеком

__PUSH__ <источник> — поместить данные в стек. Уменьшает SP на размер источника и записывает значение по адресу SS:SP.

__POP__ <приемник> — считать данные из стека. Считывает значение с адреса SS:SP и увеличивает SP.

__PUSHA__ — поместить в стек регистры AX, CX, DX, BX, SP, BP, SI, DI. (регистры общего назначения + SP + BP)

__POPA__ — загрузить регистры из стека (SP игнорируется)

## СALL и RET

__CALL__ <операнд> — передает управление на адрес <операнд>

Сохраняет адрес следующей команды в стеке (уменьшает SP и записывает по его адресу IP либо CS:IP, в зависимости от размера аргумента)

__RET__ <число> — загружает из стека адерс возврата, увеличивая SP.

Если указать операнд, то можно очистить стек для очистки стека от параметров (<число> будет прибавлено к SP)

Примеры использования

<img width="720" alt="Снимок экрана 2023-03-27 в 14 30 06" src="https://user-images.githubusercontent.com/57632162/227929262-cdf39bd1-c94d-4d7e-87ef-289185026bfd.png">

<img width="720" alt="Снимок экрана 2023-03-27 в 14 30 21" src="https://user-images.githubusercontent.com/57632162/227929331-d87c6dd9-60dc-4c91-92d9-6607d203c06d.png">

<img width="719" alt="Снимок экрана 2023-03-27 в 14 30 42" src="https://user-images.githubusercontent.com/57632162/227929417-76cfe914-6781-47a5-a109-e58239ac2695.png">

# 07. Регистр флагов.

## <!DOCTYPE html><h1 style="box-sizing: border-box; font-size: 2em; margin-top: 0px !important; margin-right: 0px; margin-bottom: 16px; margin-left: 0px; font-weight: var(--base-text-weight-semibold, 600); line-height: 1.25; padding-bottom: 0.3em; border-bottom: 1px solid var(--color-border-muted); caret-color: rgb(201, 209, 217); color: rgb(201, 209, 217); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe UI&quot;, &quot;Noto Sans&quot;, Helvetica, Arial, sans-serif, &quot;Apple Color Emoji&quot;, &quot;Segoe UI Emoji&quot;; font-style: normal; font-variant-caps: normal; letter-spacing: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: auto; word-spacing: 0px; -webkit-text-size-adjust: auto; -webkit-text-stroke-width: 0px; text-decoration: none;">Регистр флагов</h1><p style="box-sizing: border-box; margin-top: 0px; margin-bottom: 16px; caret-color: rgb(201, 209, 217); color: rgb(201, 209, 217); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe UI&quot;, &quot;Noto Sans&quot;, Helvetica, Arial, sans-serif, &quot;Apple Color Emoji&quot;, &quot;Segoe UI Emoji&quot;; font-size: 16px; font-style: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: auto; word-spacing: 0px; -webkit-text-size-adjust: auto; -webkit-text-stroke-width: 0px; text-decoration: none;">Флаги<span class="Apple-converted-space"> </span><strong style="box-sizing: border-box; font-weight: var(--base-text-weight-semibold, 600);">выставляются при операциях</strong>, но не обязательно все сразу. Например INC и DEC не затрагивают флаг CF, в отличии от ADD и SUB.</p><p style="box-sizing: border-box; margin-top: 0px; margin-bottom: 16px; caret-color: rgb(201, 209, 217); color: rgb(201, 209, 217); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe UI&quot;, &quot;Noto Sans&quot;, Helvetica, Arial, sans-serif, &quot;Apple Color Emoji&quot;, &quot;Segoe UI Emoji&quot;; font-size: 16px; font-style: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: auto; word-spacing: 0px; -webkit-text-size-adjust: auto; -webkit-text-stroke-width: 0px; text-decoration: none;">Также есть команды рассчитанные на флаги, например CMP, которая выставляет флаги такие, как если бы произошло вычитание аргументов.</p><p style="box-sizing: border-box; margin-top: 0px; margin-bottom: 16px; caret-color: rgb(201, 209, 217); color: rgb(201, 209, 217); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe UI&quot;, &quot;Noto Sans&quot;, Helvetica, Arial, sans-serif, &quot;Apple Color Emoji&quot;, &quot;Segoe UI Emoji&quot;; font-size: 16px; font-style: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: auto; word-spacing: 0px; -webkit-text-size-adjust: auto; -webkit-text-stroke-width: 0px; text-decoration: none;"><strong style="box-sizing: border-box; font-weight: var(--base-text-weight-semibold, 600);">Как мы помним, регистры у нас размером в 16 бит.</strong></p><p style="box-sizing: border-box; margin-top: 0px; margin-bottom: 16px; caret-color: rgb(201, 209, 217); color: rgb(201, 209, 217); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe UI&quot;, &quot;Noto Sans&quot;, Helvetica, Arial, sans-serif, &quot;Apple Color Emoji&quot;, &quot;Segoe UI Emoji&quot;; font-size: 16px; font-style: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: auto; word-spacing: 0px; -webkit-text-size-adjust: auto; -webkit-text-stroke-width: 0px; text-decoration: none;">Вот за что отвечает каждый бит в регистре FLAGS:</p>

0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15
-- | -- | -- | -- | -- | -- | -- | -- | -- | -- | -- | -- | -- | -- | -- | --
CF | - | PF | - | AF | - | ZF | SF | TF | IF | DF | OF | IOPL | IOPL | NT | -

<p style="box-sizing: border-box; margin-top: 0px; margin-bottom: 16px; caret-color: rgb(201, 209, 217); color: rgb(201, 209, 217); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe UI&quot;, &quot;Noto Sans&quot;, Helvetica, Arial, sans-serif, &quot;Apple Color Emoji&quot;, &quot;Segoe UI Emoji&quot;; font-size: 16px; font-style: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: auto; word-spacing: 0px; -webkit-text-size-adjust: auto; -webkit-text-stroke-width: 0px; text-decoration: none;">■ CF (carry flag) - флаг переноса - устанавливается в 1, если результат предыдущей операции не уместился в приемник и произошел перенос или если требуется заем при вычитании. Иначе 0.</p><p style="box-sizing: border-box; margin-top: 0px; margin-bottom: 16px; caret-color: rgb(201, 209, 217); color: rgb(201, 209, 217); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe UI&quot;, &quot;Noto Sans&quot;, Helvetica, Arial, sans-serif, &quot;Apple Color Emoji&quot;, &quot;Segoe UI Emoji&quot;; font-size: 16px; font-style: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: auto; word-spacing: 0px; -webkit-text-size-adjust: auto; -webkit-text-stroke-width: 0px; text-decoration: none;">■ PF (parity flag) - флаг чётности - устанавливается в 1, если младший байт результата предыдущей операции содержит четное количество единиц.</p><p style="box-sizing: border-box; margin-top: 0px; margin-bottom: 16px; caret-color: rgb(201, 209, 217); color: rgb(201, 209, 217); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe UI&quot;, &quot;Noto Sans&quot;, Helvetica, Arial, sans-serif, &quot;Apple Color Emoji&quot;, &quot;Segoe UI Emoji&quot;; font-size: 16px; font-style: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: auto; word-spacing: 0px; -webkit-text-size-adjust: auto; -webkit-text-stroke-width: 0px; text-decoration: none;">■ AF (auxiliary carry flag) - вспомогательный флаг переноса - устанавливается в 1, если в результате предыдущей операции произошел перенос из 3 в 4 или заем из 4 в 3 биты.</p><p style="box-sizing: border-box; margin-top: 0px; margin-bottom: 16px; caret-color: rgb(201, 209, 217); color: rgb(201, 209, 217); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe UI&quot;, &quot;Noto Sans&quot;, Helvetica, Arial, sans-serif, &quot;Apple Color Emoji&quot;, &quot;Segoe UI Emoji&quot;; font-size: 16px; font-style: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: auto; word-spacing: 0px; -webkit-text-size-adjust: auto; -webkit-text-stroke-width: 0px; text-decoration: none;">■ ZF (zero flag) - флаг нуля - устанавливается в 1, если если результат предыдущей команды равен 0.</p><p style="box-sizing: border-box; margin-top: 0px; margin-bottom: 16px; caret-color: rgb(201, 209, 217); color: rgb(201, 209, 217); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe UI&quot;, &quot;Noto Sans&quot;, Helvetica, Arial, sans-serif, &quot;Apple Color Emoji&quot;, &quot;Segoe UI Emoji&quot;; font-size: 16px; font-style: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: auto; word-spacing: 0px; -webkit-text-size-adjust: auto; -webkit-text-stroke-width: 0px; text-decoration: none;">■ SF (sign flag) - флаг знака - всегда равен старшему биту результата.</p><p style="box-sizing: border-box; margin-top: 0px; margin-bottom: 16px; caret-color: rgb(201, 209, 217); color: rgb(201, 209, 217); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe UI&quot;, &quot;Noto Sans&quot;, Helvetica, Arial, sans-serif, &quot;Apple Color Emoji&quot;, &quot;Segoe UI Emoji&quot;; font-size: 16px; font-style: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: auto; word-spacing: 0px; -webkit-text-size-adjust: auto; -webkit-text-stroke-width: 0px; text-decoration: none;">■ TF (trap flag) - флаг трассировки - предусмотрен для работы отладчиков в пошаговом режиме. Если поставить в 1, после каждой команды будет происходить передача управления отладчику.</p><p style="box-sizing: border-box; margin-top: 0px; margin-bottom: 16px; caret-color: rgb(201, 209, 217); color: rgb(201, 209, 217); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe UI&quot;, &quot;Noto Sans&quot;, Helvetica, Arial, sans-serif, &quot;Apple Color Emoji&quot;, &quot;Segoe UI Emoji&quot;; font-size: 16px; font-style: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: auto; word-spacing: 0px; -webkit-text-size-adjust: auto; -webkit-text-stroke-width: 0px; text-decoration: none;">■ IF (interrupt enable flag) - флаг разрешения прерываний - если 0 процессор перестает обрабатывать прерывания от внешних устройств.</p><p style="box-sizing: border-box; margin-top: 0px; margin-bottom: 16px; caret-color: rgb(201, 209, 217); color: rgb(201, 209, 217); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe UI&quot;, &quot;Noto Sans&quot;, Helvetica, Arial, sans-serif, &quot;Apple Color Emoji&quot;, &quot;Segoe UI Emoji&quot;; font-size: 16px; font-style: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: auto; word-spacing: 0px; -webkit-text-size-adjust: auto; -webkit-text-stroke-width: 0px; text-decoration: none;">■ DF (direction flag) - флаг направления - контролирует поведение команд обработки строк. Если 0, строки обрабатываются слева направо, если 1 справа налево.</p><p style="box-sizing: border-box; margin-top: 0px; margin-bottom: 16px; caret-color: rgb(201, 209, 217); color: rgb(201, 209, 217); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe UI&quot;, &quot;Noto Sans&quot;, Helvetica, Arial, sans-serif, &quot;Apple Color Emoji&quot;, &quot;Segoe UI Emoji&quot;; font-size: 16px; font-style: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: auto; word-spacing: 0px; -webkit-text-size-adjust: auto; -webkit-text-stroke-width: 0px; text-decoration: none;">■ OF (overflowflag) - флаг переполнения - устанавливается в 1, если результат предыдущей операции над числами со знаком выходит за допустимые для них пределы.</p><p style="box-sizing: border-box; margin-top: 0px; margin-bottom: 16px; caret-color: rgb(201, 209, 217); color: rgb(201, 209, 217); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe UI&quot;, &quot;Noto Sans&quot;, Helvetica, Arial, sans-serif, &quot;Apple Color Emoji&quot;, &quot;Segoe UI Emoji&quot;; font-size: 16px; font-style: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: auto; word-spacing: 0px; -webkit-text-size-adjust: auto; -webkit-text-stroke-width: 0px; text-decoration: none;">■ IOPL (I/O privilege level) - уровень приоритета ввода-вывода - а это на 286, на не нужно пока.</p><p style="box-sizing: border-box; margin-top: 0px; margin-bottom: 0px !important; caret-color: rgb(201, 209, 217); color: rgb(201, 209, 217); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe UI&quot;, &quot;Noto Sans&quot;, Helvetica, Arial, sans-serif, &quot;Apple Color Emoji&quot;, &quot;Segoe UI Emoji&quot;; font-size: 16px; font-style: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: auto; word-spacing: 0px; -webkit-text-size-adjust: auto; -webkit-text-stroke-width: 0px; text-decoration: none;">■ NT (nested task) - флаг вложенности задач - а это на 286, на не нужно пока.</p>

# 08. Команды условной и безусловной передачи управления.

<!DOCTYPE html><p style="box-sizing: border-box; margin-top: 0px !important; margin-bottom: 16px; caret-color: rgb(201, 209, 217); color: rgb(201, 209, 217); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe UI&quot;, &quot;Noto Sans&quot;, Helvetica, Arial, sans-serif, &quot;Apple Color Emoji&quot;, &quot;Segoe UI Emoji&quot;; font-size: 16px; font-style: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: auto; word-spacing: 0px; -webkit-text-size-adjust: auto; -webkit-text-stroke-width: 0px; text-decoration: none;"><strong style="box-sizing: border-box; font-weight: var(--base-text-weight-semibold, 600);">Условный переход</strong><span class="Apple-converted-space"> </span>- переход, происходящий при выполнении какого-то условия.</p><p style="box-sizing: border-box; margin-top: 0px; margin-bottom: 16px; caret-color: rgb(201, 209, 217); color: rgb(201, 209, 217); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe UI&quot;, &quot;Noto Sans&quot;, Helvetica, Arial, sans-serif, &quot;Apple Color Emoji&quot;, &quot;Segoe UI Emoji&quot;; font-size: 16px; font-style: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: auto; word-spacing: 0px; -webkit-text-size-adjust: auto; -webkit-text-stroke-width: 0px; text-decoration: none;"><strong style="box-sizing: border-box; font-weight: var(--base-text-weight-semibold, 600);">Безусловный переход</strong><span class="Apple-converted-space"> </span>- переход, не зависящий от чего-либо (совершаемый в любом случае).</p><h1 style="box-sizing: border-box; font-size: 2em; margin: 24px 0px 16px; font-weight: var(--base-text-weight-semibold, 600); line-height: 1.25; padding-bottom: 0.3em; border-bottom: 1px solid var(--color-border-muted); caret-color: rgb(201, 209, 217); color: rgb(201, 209, 217); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe UI&quot;, &quot;Noto Sans&quot;, Helvetica, Arial, sans-serif, &quot;Apple Color Emoji&quot;, &quot;Segoe UI Emoji&quot;; font-style: normal; font-variant-caps: normal; letter-spacing: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: auto; word-spacing: 0px; -webkit-text-size-adjust: auto; -webkit-text-stroke-width: 0px; text-decoration: none;"><a id="user-content-виды-безусловных-переходов" class="anchor" aria-hidden="true" href="#виды-безусловных-переходов" style="box-sizing: border-box; background-color: transparent; color: var(--color-accent-fg); text-decoration: none; float: left; padding-right: 4px; margin-left: -20px; line-height: 1;"><svg class="octicon octicon-link" viewBox="0 0 16 16" version="1.1" width="16" height="16" aria-hidden="true"><path d="m7.775 3.275 1.25-1.25a3.5 3.5 0 1 1 4.95 4.95l-2.5 2.5a3.5 3.5 0 0 1-4.95 0 .751.751 0 0 1 .018-1.042.751.751 0 0 1 1.042-.018 1.998 1.998 0 0 0 2.83 0l2.5-2.5a2.002 2.002 0 0 0-2.83-2.83l-1.25 1.25a.751.751 0 0 1-1.042-.018.751.751 0 0 1-.018-1.042Zm-4.69 9.64a1.998 1.998 0 0 0 2.83 0l1.25-1.25a.751.751 0 0 1 1.042.018.751.751 0 0 1 .018 1.042l-1.25 1.25a3.5 3.5 0 1 1-4.95-4.95l2.5-2.5a3.5 3.5 0 0 1 4.95 0 .751.751 0 0 1-.018 1.042.751.751 0 0 1-1.042.018 1.998 1.998 0 0 0-2.83 0l-2.5 2.5a1.998 1.998 0 0 0 0 2.83Z"></path></svg></a>Виды безусловных переходов</h1><p style="box-sizing: border-box; margin-top: 0px; margin-bottom: 16px; caret-color: rgb(201, 209, 217); color: rgb(201, 209, 217); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe UI&quot;, &quot;Noto Sans&quot;, Helvetica, Arial, sans-serif, &quot;Apple Color Emoji&quot;, &quot;Segoe UI Emoji&quot;; font-size: 16px; font-style: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: auto; word-spacing: 0px; -webkit-text-size-adjust: auto; -webkit-text-stroke-width: 0px; text-decoration: none;"><strong style="box-sizing: border-box; font-weight: var(--base-text-weight-semibold, 600);">JMP</strong><span class="Apple-converted-space"> </span>- оператор безусловного перехода.</p>

Вид перехода | Дистанция перехода
-- | --
short (короткий) | -128..+127 байт
near (ближний) | в том же сегменте (без изменения CS)
far (дальний) | в другой сегмент (со сменой CS)

<h1 style="box-sizing: border-box; font-size: 2em; margin: 24px 0px 16px; font-weight: var(--base-text-weight-semibold, 600); line-height: 1.25; padding-bottom: 0.3em; border-bottom: 1px solid var(--color-border-muted); caret-color: rgb(201, 209, 217); color: rgb(201, 209, 217); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe UI&quot;, &quot;Noto Sans&quot;, Helvetica, Arial, sans-serif, &quot;Apple Color Emoji&quot;, &quot;Segoe UI Emoji&quot;; font-style: normal; font-variant-caps: normal; letter-spacing: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: auto; word-spacing: 0px; -webkit-text-size-adjust: auto; -webkit-text-stroke-width: 0px; text-decoration: none;"><a id="user-content-команды-выставляющие-флаги-и-использующиеся-при-переходах-к-передаче-управления" class="anchor" aria-hidden="true" href="#команды-выставляющие-флаги-и-использующиеся-при-переходах-к-передаче-управления" style="box-sizing: border-box; background-color: transparent; color: var(--color-accent-fg); text-decoration: none; float: left; padding-right: 4px; margin-left: -20px; line-height: 1;"><svg class="octicon octicon-link" viewBox="0 0 16 16" version="1.1" width="16" height="16" aria-hidden="true"><path d="m7.775 3.275 1.25-1.25a3.5 3.5 0 1 1 4.95 4.95l-2.5 2.5a3.5 3.5 0 0 1-4.95 0 .751.751 0 0 1 .018-1.042.751.751 0 0 1 1.042-.018 1.998 1.998 0 0 0 2.83 0l2.5-2.5a2.002 2.002 0 0 0-2.83-2.83l-1.25 1.25a.751.751 0 0 1-1.042-.018.751.751 0 0 1-.018-1.042Zm-4.69 9.64a1.998 1.998 0 0 0 2.83 0l1.25-1.25a.751.751 0 0 1 1.042.018.751.751 0 0 1 .018 1.042l-1.25 1.25a3.5 3.5 0 1 1-4.95-4.95l2.5-2.5a3.5 3.5 0 0 1 4.95 0 .751.751 0 0 1-.018 1.042.751.751 0 0 1-1.042.018 1.998 1.998 0 0 0-2.83 0l-2.5 2.5a1.998 1.998 0 0 0 0 2.83Z"></path></svg></a>Команды, выставляющие флаги и использующиеся при переходах к передаче управления</h1><h2 style="box-sizing: border-box; margin-top: 24px; margin-bottom: 16px; font-size: 1.5em; font-weight: var(--base-text-weight-semibold, 600); line-height: 1.25; padding-bottom: 0.3em; border-bottom: 1px solid var(--color-border-muted); caret-color: rgb(201, 209, 217); color: rgb(201, 209, 217); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe UI&quot;, &quot;Noto Sans&quot;, Helvetica, Arial, sans-serif, &quot;Apple Color Emoji&quot;, &quot;Segoe UI Emoji&quot;; font-style: normal; font-variant-caps: normal; letter-spacing: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: auto; word-spacing: 0px; -webkit-text-size-adjust: auto; -webkit-text-stroke-width: 0px; text-decoration: none;"><a id="user-content-cmp-приемник-источник" class="anchor" aria-hidden="true" href="#cmp-приемник-источник" style="box-sizing: border-box; background-color: transparent; color: var(--color-accent-fg); text-decoration: none; float: left; padding-right: 4px; margin-left: -20px; line-height: 1;"><svg class="octicon octicon-link" viewBox="0 0 16 16" version="1.1" width="16" height="16" aria-hidden="true"><path d="m7.775 3.275 1.25-1.25a3.5 3.5 0 1 1 4.95 4.95l-2.5 2.5a3.5 3.5 0 0 1-4.95 0 .751.751 0 0 1 .018-1.042.751.751 0 0 1 1.042-.018 1.998 1.998 0 0 0 2.83 0l2.5-2.5a2.002 2.002 0 0 0-2.83-2.83l-1.25 1.25a.751.751 0 0 1-1.042-.018.751.751 0 0 1-.018-1.042Zm-4.69 9.64a1.998 1.998 0 0 0 2.83 0l1.25-1.25a.751.751 0 0 1 1.042.018.751.751 0 0 1 .018 1.042l-1.25 1.25a3.5 3.5 0 1 1-4.95-4.95l2.5-2.5a3.5 3.5 0 0 1 4.95 0 .751.751 0 0 1-.018 1.042.751.751 0 0 1-1.042.018 1.998 1.998 0 0 0-2.83 0l-2.5 2.5a1.998 1.998 0 0 0 0 2.83Z"></path></svg></a>CMP &lt;приемник&gt;, &lt;источник&gt;</h2><p style="box-sizing: border-box; margin-top: 0px; margin-bottom: 16px; caret-color: rgb(201, 209, 217); color: rgb(201, 209, 217); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe UI&quot;, &quot;Noto Sans&quot;, Helvetica, Arial, sans-serif, &quot;Apple Color Emoji&quot;, &quot;Segoe UI Emoji&quot;; font-size: 16px; font-style: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: auto; word-spacing: 0px; -webkit-text-size-adjust: auto; -webkit-text-stroke-width: 0px; text-decoration: none;"><strong style="box-sizing: border-box; font-weight: var(--base-text-weight-semibold, 600);">Источник</strong><span class="Apple-converted-space"> </span>- число, регистр или переменная.<br style="box-sizing: border-box;"><strong style="box-sizing: border-box; font-weight: var(--base-text-weight-semibold, 600);">Приемник</strong><span class="Apple-converted-space"> </span>- регистр или переменная; не может быть переменной одновременно с источником.</p><p style="box-sizing: border-box; margin-top: 0px; margin-bottom: 16px; caret-color: rgb(201, 209, 217); color: rgb(201, 209, 217); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe UI&quot;, &quot;Noto Sans&quot;, Helvetica, Arial, sans-serif, &quot;Apple Color Emoji&quot;, &quot;Segoe UI Emoji&quot;; font-size: 16px; font-style: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: auto; word-spacing: 0px; -webkit-text-size-adjust: auto; -webkit-text-stroke-width: 0px; text-decoration: none;">Вычитает источник из приёмника, результат никуда не сохраняется, выставляются флаги<span class="Apple-converted-space"> </span><strong style="box-sizing: border-box; font-weight: var(--base-text-weight-semibold, 600);">CF, PF, AF, ZF, SF, OF</strong>.</p><h2 style="box-sizing: border-box; margin-top: 24px; margin-bottom: 16px; font-size: 1.5em; font-weight: var(--base-text-weight-semibold, 600); line-height: 1.25; padding-bottom: 0.3em; border-bottom: 1px solid var(--color-border-muted); caret-color: rgb(201, 209, 217); color: rgb(201, 209, 217); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe UI&quot;, &quot;Noto Sans&quot;, Helvetica, Arial, sans-serif, &quot;Apple Color Emoji&quot;, &quot;Segoe UI Emoji&quot;; font-style: normal; font-variant-caps: normal; letter-spacing: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: auto; word-spacing: 0px; -webkit-text-size-adjust: auto; -webkit-text-stroke-width: 0px; text-decoration: none;"><a id="user-content-test-приемник-источник" class="anchor" aria-hidden="true" href="#test-приемник-источник" style="box-sizing: border-box; background-color: transparent; color: var(--color-accent-fg); text-decoration: none; float: left; padding-right: 4px; margin-left: -20px; line-height: 1;"><svg class="octicon octicon-link" viewBox="0 0 16 16" version="1.1" width="16" height="16" aria-hidden="true"><path d="m7.775 3.275 1.25-1.25a3.5 3.5 0 1 1 4.95 4.95l-2.5 2.5a3.5 3.5 0 0 1-4.95 0 .751.751 0 0 1 .018-1.042.751.751 0 0 1 1.042-.018 1.998 1.998 0 0 0 2.83 0l2.5-2.5a2.002 2.002 0 0 0-2.83-2.83l-1.25 1.25a.751.751 0 0 1-1.042-.018.751.751 0 0 1-.018-1.042Zm-4.69 9.64a1.998 1.998 0 0 0 2.83 0l1.25-1.25a.751.751 0 0 1 1.042.018.751.751 0 0 1 .018 1.042l-1.25 1.25a3.5 3.5 0 1 1-4.95-4.95l2.5-2.5a3.5 3.5 0 0 1 4.95 0 .751.751 0 0 1-.018 1.042.751.751 0 0 1-1.042.018 1.998 1.998 0 0 0-2.83 0l-2.5 2.5a1.998 1.998 0 0 0 0 2.83Z"></path></svg></a>TEST &lt;приемник&gt;, &lt;источник&gt;</h2><p style="box-sizing: border-box; margin-top: 0px; margin-bottom: 0px !important; caret-color: rgb(201, 209, 217); color: rgb(201, 209, 217); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe UI&quot;, &quot;Noto Sans&quot;, Helvetica, Arial, sans-serif, &quot;Apple Color Emoji&quot;, &quot;Segoe UI Emoji&quot;; font-size: 16px; font-style: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: auto; word-spacing: 0px; -webkit-text-size-adjust: auto; -webkit-text-stroke-width: 0px; text-decoration: none;">Аналог<span class="Apple-converted-space"> </span><strong style="box-sizing: border-box; font-weight: var(--base-text-weight-semibold, 600);">AND</strong>, но результат не сохраняется. Выставляются флаги<span class="Apple-converted-space"> </span><strong style="box-sizing: border-box; font-weight: var(--base-text-weight-semibold, 600);">SF, ZF, PF</strong>.</p>

# 09. Организация многомодульных программ.

## Организация многомодульных программ

Как и на других языках программирования, программа на ассемблере может состоять из нескольких файлов - модулей. При компиляции (трансляции) каждый модуль превращается в объектный файл, далее при компоновке объектные файлы соединяются в единый исполняемый модуль.

Модули обычно состоят из описания сегментов будущей программы с помощью директивы SEGMENT.

Пример:

```assembler
имя SEGMENT [READONLY] выравнивание тип разряд 'класс' 
… 
имя ENDS
```
Параметры:

● Выравнивание - расположение начала сегмента с адреса, кратного какому-либо значению. Варианты:

BYTE;

WORD (2 байта);

DWORD (4 байта);

PARA (16 байт, по умолчанию);

PAGE (256 байт).

● Тип:

PUBLIC (сегменты с одним именем объединятся в один);

STACK (для стека); COMMON (сегменты будут “наложены” друг на друга по одним и тем же адресам памяти);

AT <начало> - расположение по фиксированному физическому адресу, параметр - сегментная часть этого адреса;

PRIVATE - вариант по умолчанию.

● Класс - метка, позволяющая объединить сегменты (расположить в памяти друг за другом).

# 10. Подпрограммы. Объявление, вызов.

## Описание подпрограммы

```assembler
имя_подпрограммы PROC [NEAR | FAR] ; по умолчанию NEAR, если не указать
    ;тело подпрограммы; 
    ret [кол-во используемых локальный переменных] ; ничего не указывается, если не использовались локальные переменные на стеке
имя_подпрограммы ENDP
```
## Вызов подпрограммы

```
; вызов любой (в плане расстояния) подпрограммы
call имя_подпрограммы
```

## CALL - вызов процедуры, RET - возврат из процедуры

__CALL <операнд>__

* Сохраняет адрес следующей команды в стеке (уменьшает SP и записывает по его адресу IP либо CS:IP, в зависимости от размера аргумента)
* Передаёт управление на значение аргумента.

__RET/RETN/RETF <число>__

* Загружает из стека адрес возврата, увеличивает SP
* Если указан операнд, его значение будет дополнительно прибавлено к SP для очистки стека от параметров

Отличие RETN и RETF в том, что 1ая команда делает возврат при ближнем переходе, 2ая - при дальнем (различие в кол-ве байт, считываемых из стека при возврате). Если используется RET, то ассемблер сам выберет между RETN и RETF в зависимости от описание подпрограммы (процедуры).

__BP – base pointer__

* Используется в подпрограмме для сохранения "начального" значения SP
* Адресация параметров
* Адресация локальных переменных
(подробнее см. стек)

# 11. Арифметические команды.

## Арифметические команды.

### ADD и ADC

__ADD__ <приемник>, <источник> — сложение. Не делает различий между знаковыми и беззнаковыми числами.

__ADC__ <приемник>, <источник> — сложение с переносом. Складывает приёмник, источник и флаг CF.

### SUB и SBB

__SUB__ <приемник>, <источник> — вычитание. Не делает различий между знаковыми и беззнаковыми числами.

__SBB__ <приемник>, <источник> — вычитание с займом. Вычитает из приёмника источник и дополнительно - флаг CF.

Флаг __CF__ можно рассматривать как дополнительный бит у результата.

<img width="491" alt="Снимок экрана 2023-03-27 в 14 40 05" src="https://user-images.githubusercontent.com/57632162/227931248-f9e288bf-310d-4d57-8ea0-efe5f5f0f7ff.png">

Можно использовать ADC и SBB для сложения вычитания и больших чисел, которые по частям храним в двух регистрах.

__Пример__: Сложим два 32-битных числа. Пусть одно из них хранится в паре регистров DX:AX (младшее двойное слово - DX, старшее AX). Другое в паре BX:CX

```assembler
add ax, cx
adc dx, bx
```

Если при сложении двойных слов произошел перенос из старшего разряда, то это будет учтено командой adc.

Эти 4 команды (ADD, ADC, SUB, SBB) меняют флаги: CF, OF, SF, ZF, AF, PF

### MUL и IMUL

__MUL__ <источник> — выполняет умножение чисел без знака. <источник> не может быть число (нельзя: MUL 228). Умножает регистр AX (AL), на <источник>. Результат остается в AX, либо DX:AX, если не помещается в AX.

__IMUL__ — умножение чисел со знаком.

1. __IMUL__ <источник>. Работает так же, как и MUL
2. __IMUL__ <приёмник>, <источник>. Умножает источник на приемник, результат в приемник.
3. __IMUL__ <приёмник>, <источник1>, <источник2>. Умножает источник1 на источник2, результат в приёмник.
__Флаги__: OF, CF

### DIV и IDIV

__DIV__ <источник> — выполняет деление чисел без знака. <источник> не может быть число (нельзя: DIV 228). Делимое должно быть помещено в AX (или DX:AX, если делитель больше байта). В первом случае частное в AL, остаток в AH, во втором случае частное в AX, остаток в DX.

__IDIV__ <источник> — деление чисел со знаком. Работает так же как и DIV. Окруление в сторону нуля, знак остатка совпадает со знаком делимого.

### INC, DEC, NOT

__INC__ <приемник> — увеличивает примник на 1.

__DEC__ <приемник> — уменьшает примник на 1.

__Меняют флаги__: OF, SF, ZF, AF, PF

__NEG__ <применик> — меняет знак приемника.

# 12. Команды побитовых операций.

## Операции над битами и байтами

### BT <база>, <смещение>

Считывает в CF значение бита из битовой строчки.

### BTS <база>, <смещение>

Устанавливает бит в 1.

### BTR <база>, <смещение>

Сбрасывавет бит в 0.

### BTC <база>, <смещение>

Инвертирует бит.

### BSF <приемник>, <смещение>

Прямой поиск бита (от младшего разряда).

### BSR <приемник>, <смещение>

Обратный поиск бита (от старшего разряда).

### SETcc <приемник>

Выставляет приемник (1 байт) в 1 или 0 в зависимости от условия, аналогично Jcc.

## Логический, арифметический, циклический сдвиг

### SAL (SHL)

Арифметический сдвиг налево.

### SHR

Логический сдвиг направо, зануляет старший бит.

### SAR

Арифметический сдвиг направо, сохраняет знак.

### ROR (ROL)

Циклический сдивг вправо (влево).

### RCR (RCL)

Циклический сдвиг вправо (влево) через CF.

# 13. Команды работы со строками.

## Строковые операции: ```копирование```, ```сравнение```, ```сканирование```, ```чтение```, ```запись```

Строка-источник - ```DS:SI```, строка-приёмник - ```ES:DI```.

За один раз обрабатывается один байт (слово).

* ```MOVS``` / ```MOVSB``` / ```MOVSW``` ```<приёмник>, <источник>``` - копирование

* ```CMPS``` / ```CMPSB``` / ```CMPSW``` ```<приёмник>, <источник>``` - сравнение

* ```SCAS``` / ```SCASB``` / ```SCASW``` ```<приёмник>``` - сканирование (сравнение с AL/AX (в зависимости от размеров приемника)

* ```LODS``` / ```LODSB``` / ```LODSW``` ```<источник>``` - чтение (в ```AL/AX```)

* ```STOS``` / ```STOSB``` / ```STOSW``` ```<приёмник>``` - запись (из ```AL/AX```)

* Префиксы: ```REP``` / ```REPE``` / ```REPZ``` / ```REPNE``` / ```REPNZ```

* ```REP``` - повторить следующую строковую операцию

* ```REPE``` - повторить следующую строковую операцию, если равно

* ```REPZ``` - Повторить следующую строковую операцию, если нуль

* ```REPNE``` - повторить следующую строковую операцию, если не равно

* ```REPNZ``` - повторить следующую строковую операцию, если не нуль

Префиксы ```REP``` (```F3h```), ```REPE``` (```F3h```) и ```REPNE``` (```F2h```) применяются со строковыми операциями. Каждый префикс заставляет строковую команду, которая следует за ним, повторяться указанное в регистре счетчике ```(E)CX``` (в случае нашей модели процессора ```8086``` - ```CX```) количество раз или, кроме этого, (для префиксов ```REPE``` и ```REPNE```) пока не встретится указанное условие во флаге ```ZF```.

Пример использования: ```REP LODS AX```

Мнемоники ```REPZ``` и ```REPNZ``` являются синонимами префиксов ```REPE``` и ```REPNE``` соответственно и имеют одинаковые с ними коды. Префиксы ```REP``` и ```REPE``` / ```REPZ``` также имеют одинаковый код ```F3h```, конкретный тип префикса задается неявно той командой, перед которой он применен.

Все описываемые префиксы могут применяются только к одной строковой команде за один раз. Чтобы повторить блок команд, используется команда ```LOOP``` или другие циклические конструкции.

Затрагиваемые флаги: ```OF```, ```DF```, ```IF```, ```TF```, ```SF```, ```ZF```, ```AF```, ```PF```, ```CF```
