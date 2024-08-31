#include <iostream>
#include <vector>

std::vector<std::vector<int>> data = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0}
};

const std::vector<std::vector<int>> backup_data = data;

bool can_continue(const std::vector<std::vector<int>>& data, int row, int cell, int iteration) {
    int start_row_position = (row / 3) * 3;
    int start_cell_position = (cell / 3) * 3;

    for (int i = 0; i < 9; ++i)
        if (data[row][i] == iteration || data[i][cell] == iteration || data[start_row_position + i / 3][start_cell_position + i % 3] == iteration)
            return false;

    return true;
};

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

void print_result(const std::vector<std::vector<int>>& backup_data, const std::vector<std::vector<int>>& data, bool successfull) {
    std::cout << "----------START----------" << (successfull ? "    ----------SOLVE----------\n" : "    No possible solutions exist :(\n");

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (j % 3 == 0)
                std::cout << "| ";

            if (backup_data[i][j] == 0)
                std::cout << "  ";
            else
                std::cout << backup_data[i][j] << " ";
        }

        if (successfull)
        {
            std::cout << "|    ";

            for (int j = 0; j < 9; ++j) {
                if (j % 3 == 0)
                    std::cout << "| ";

                if (data[i][j] == 0)
                    std::cout << "  ";
                else
                    std::cout << data[i][j] << " ";
            }
        }

        std::cout << "|\n";

        if ((i + 1) % 3 == 0)
            std::cout << (successfull ? ("-------------------------    -------------------------\n") : ("-------------------------\n"));
    }
};

int main() {
    print_result(backup_data, data, process_solve(data));
    return 0;
}
