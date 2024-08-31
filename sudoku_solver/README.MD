## [RU] Объяснение
Простая реализация решение любого судоку с помощью метода возврата к исходным данным (backtracking).\
На этих скриншотах вы видите последовательность событий, которые произойдут при выполнении данного кода.

<p float="left">
  <img src="https://i.imgur.com/AmKqai1.png" width=21% height=22%>
  <img src="https://i.imgur.com/rnZH35L.png" width=30% height=30%>
  <img src="https://i.imgur.com/NUrHVft.png" width=37% height=42%>
</p>

### Определение данных для судоку
[data] -> вектор, представляющий собой сетку судоку 9x9. Нули обозначают пустые клетки, которые нужно заполнить.

```c++
std::vector<std::vector<int>> data = {
    {0, 6, 0, 0, 4, 5, 3, 7, 0},
    {0, 0, 5, 6, 7, 3, 4, 2, 0},
    {0, 0, 4, 0, 0, 0, 0, 0, 1},
    {5, 0, 0, 7, 0, 2, 0, 0, 4},
    {6, 0, 9, 0, 0, 0, 2, 5, 0},
    {8, 0, 7, 0, 0, 9, 0, 0, 3},
    {4, 9, 0, 5, 1, 7, 8, 0, 0},
    {2, 1, 0, 0, 3, 6, 0, 0, 0},
    {0, 5, 0, 0, 2, 0, 1, 0, 0}
};
```

[backup_data] -> сохраняет начальное состояние сетки судоку для отображения его рядом с решением.
```c++
const std::vector<std::vector<int>> backup_data = data;
```

### Функция проверки возможности продолжения
[can_continue] -> функция проверяет возможность размещения числа в клетке `data[row][cell]`

```c++
bool can_continue(const std::vector<std::vector<int>>& data, int row, int cell, int iteration) {
    int start_row_position = (row / 3) * 3;
    int start_cell_position = (cell / 3) * 3;

    for (int i = 0; i < 9; ++i)
        if (data[row][i] == iteration || data[i][cell] == iteration || data[start_row_position + i / 3][start_cell_position + i % 3] == iteration)
            return false;

    return true;
};
```

### Функция решения судоку
[can_continue] -> рекурсивная функция, которая и производит процесс решения судоку.
* если мы достигли конца строки `row == 9`, значит решение найдено). Если же `cell == 9`, то переходим к следующей строке.
* если клетка заполнена `data[row][cell] != 0`, то переходим к другой клетке.
* если `can_continue` возвращает `true`, то вставляем найденное число в клетку и рекурсивно решаем дальше.
* если вставленное число не приводит к решению, то возвращаем клетку в исходное состояние `data[row][cell] = 0`.

```c++
bool process_solve(std::vector<std::vector<int>>& data, int row = 0, int cell = 0) {
    if (row == 9)
        return true;

    if (cell == 9)
        return process_solve(data, row + 1, 0);

    if (data[row][cell] != 0)
        return process_solve(data, row, cell + 1);

    for (int i = 1; i <= 9; ++i) {
        if (can_continue(data, row, cell, i)) {
            data[row][cell] = i;

            if (process_solve(data, row, cell + 1))
                return true;

            data[row][cell] = 0;
        }
    }

    return false;
};
```

## [EN] Explanation
