//
// Created by shesh on 10/14/2024.
//

#include "KnightMoves6.h"

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

void getValidMoves(const std::vector<std::vector<std::pair<std::string, char>>>& board,
                   std::vector<std::pair<int, int>>& knightMoves,
                   std::unordered_set<std::string>& visitedCoors, const int startRow, const int startCol,
                   const int endRow,
                   const int endCol, std::vector<std::string>& currPath, std::vector<std::string>& validMoves,
                   const int maxDepth)
{
    if (startRow == endRow && startCol == endCol)
    {
        std::string concatanated{};

        for (auto& path : currPath)
        {
            concatanated.append(path);
        }

        validMoves.push_back(concatanated);
        return;
    }
    else if (currPath.size() <= maxDepth)
    {
        for (int i = 0; i < knightMoves.size(); ++i)
        {
            const int dx = knightMoves[i].first;
            const int dy = knightMoves[i].second;
            const int newRow = startRow + dx;
            const int newCol = startCol + dy;

            if (0 <= newRow && newRow < board.size() && 0 <= newCol && newCol < board[0].size() && visitedCoors.find(
                std::get<0>(board[newRow][newCol])) == visitedCoors.end())
            {
                visitedCoors.insert(std::get<0>(board[newRow][newCol]));
                currPath.push_back(
                    ",{" + std::get<0>(board[newRow][newCol]) + "," + std::get<1>(board[newRow][newCol]) + "}");
                getValidMoves(board, knightMoves, visitedCoors, newRow, newCol, endRow, endCol, currPath, validMoves,
                              maxDepth);
                currPath.pop_back();
                visitedCoors.erase(std::get<0>(board[newRow][newCol]));
            }
        }
    }
}

std::string getValuePath(const std::string& currPath)
{
    std::string value{};

    for (int i = 0; i < currPath.size() - 1; ++i)
    {
        if (currPath[i + 1] == '}') value.push_back(currPath[i]);
    }
    return value;
}

bool equal2024(std::unordered_map<char, int>& valueMapping, const std::string& currPath)
{
    std::string valuePath = getValuePath(currPath);
    int res = valueMapping['A'];
    for (int i = 1; i < valuePath.size(); ++i)
    {
        if (valuePath[i - 1] == valuePath[i])
        {
            res += valueMapping[valuePath[i]];
        }
        else
        {
            res *= valueMapping[valuePath[i]];
        }
    }

    return res == 2024;
}


int main()
{
    const std::vector<std::vector<std::pair<std::string, char>>> board = {
        {{"A1", 'A'}, {"B1", 'A'}, {"C1", 'A'}, {"D1", 'B'}, {"E1", 'B'}, {"F1", 'C'}},
        {{"A2", 'A'}, {"B2", 'A'}, {"C2", 'A'}, {"D2", 'B'}, {"E2", 'B'}, {"F2", 'C'}},
        {{"A3", 'A'}, {"B3", 'A'}, {"C3", 'B'}, {"D3", 'B'}, {"E3", 'C'}, {"F3", 'C'}},
        {{"A4", 'A'}, {"B4", 'A'}, {"C4", 'B'}, {"D4", 'B'}, {"E4", 'C'}, {"F4", 'C'}},
        {{"A5", 'A'}, {"B5", 'B'}, {"C5", 'B'}, {"D5", 'C'}, {"E5", 'C'}, {"F5", 'C'}},
        {{"A6", 'A'}, {"B6", 'B'}, {"C6", 'B'}, {"D6", 'C'}, {"E6", 'C'}, {"F6", 'C'}}
    };

    std::vector<std::pair<int, int>> knightMoves = {
        {2, 1}, {2, -1},
        {-2, 1}, {-2, -1},
        {1, 2}, {1, -2},
        {-1, 2}, {-1, -2}
    };

    std::unordered_set<std::string> visitedCoors{};
    std::vector<std::string> firstPath{};
    std::vector<std::string> currPath{"{A1,A}"};
    visitedCoors.emplace("A1");
    getValidMoves(board, knightMoves, visitedCoors, 0, 0, board.size() - 1, board[0].size() - 1, currPath, firstPath,
                  10);

    visitedCoors.erase("A1");
    currPath.pop_back();
    std::vector<std::string> secondPath{};
    visitedCoors.emplace("A6");
    currPath.emplace_back("{A6,A}");
    getValidMoves(board, knightMoves, visitedCoors, board.size() - 1, 0, 0, board[0].size() - 1, currPath, secondPath,
                  10);


    std::map<int, std::string> result{};

    for (int a = 1; a < 50; ++a)
    {
        for (int b = 1; b < 50; ++b)
        {
            for (int c = 1; c < 50; ++c)
            {
                if (a != b && b != c && a + c + b < 50)
                {
                    std::vector<std::string> validPathsForFirst{};

                    std::unordered_map<char, int> valueMapping{
                        {'A', a},
                        {'B', b},
                        {'C', c}
                    };

                    for (auto& path : firstPath)
                    {
                        if (equal2024(valueMapping, path)) validPathsForFirst.emplace_back(path);
                    }

                    std::vector<std::string> validPathsForSecond{};

                    for (auto& path : secondPath)
                    {
                        if (equal2024(valueMapping, path)) validPathsForSecond.emplace_back(path);
                    }

                    if (!validPathsForFirst.empty() && !validPathsForSecond.empty())
                    {
                        std::string val{};
                        val.append("Answer is A = " + std::to_string(a) +
                            " B = " + std::to_string(b) +
                            " C = " + std::to_string(c) + "\n");


                        val.append("Valid Paths for the First One: \n");
                        for (auto& path : validPathsForFirst) val.append(path + "\n");

                        val.append("Valid Paths for the Second One: \n");
                        for (auto& path : validPathsForSecond) val.append(path + "\n");

                        int key = a + b + c;
                        result[key] = val;
                    }
                }
            }
        }
    }

    if (!result.empty())
    {
        for (const auto& pair : result)
        {
            std::cout << pair.first << " " << pair.second << std::endl;
            break;
        }
    }
    return 0;
}
