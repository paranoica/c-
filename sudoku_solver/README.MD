## [RU] Объяснение
Простая реализация решение любого судоку с помощью метода возврата к исходным данным (backtracking).\
На этих скриншотах вы видите последовательность событий, которые произойдут при выполнении данного кода.

<p float="left">
  <img src="https://i.imgur.com/AmKqai1.png" width=21% height=22%>
  <img src="https://i.imgur.com/rnZH35L.png" width=30% height=30%>
  <img src="https://i.imgur.com/NUrHVft.png" width=37% height=42%>
</p>

## Определение данных для судоку
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

## Функция проверки возможности продолжения
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

## Функция решения судоку
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
A simple implementation of solving any sudoku using the backtracking method.\
These screenshots show the sequence of events that will happen when this code is executed.

<p float="left">
  <img src="https://i.imgur.com/AmKqai1.png" width=21% height=22%>
  <img src="https://i.imgur.com/rnZH35L.png" width=30% height=30%>
  <img src="https://i.imgur.com/NUrHVft.png" width=37% height=42%>
</p>

## Defining sudoku data
[data] -> a vector representing a 9x9 sudoku grid. The zeros represent empty cells that need to be filled.

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

[backup_data] -> saves the initial state of the sudoku grid to display it next to the solution.
```c++
const std::vector<std::vector<int>> backup_data = data;
```

## Function to check whether it is possible to continue
[can_continue] -> function checks whether it is possible to place a number in the cell `data[row][cell]`

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

## Sudoku solving function
[can_continue] -> recursive function that performs the process of solving sudoku.
* if we have reached the end of the line `row == 9`, then the solution has been found). If `cell == 9`, then we move on to the next line.
* if the cell is filled with `data[row][cell] != 0`, then we move on to another cell.
* if `can_continue` returns `true`, then we insert the found number into the cell and continue solving recursively.
* if the inserted number does not lead to a solution, then we return the cell to its original state `data[row][cell] = 0`.

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
