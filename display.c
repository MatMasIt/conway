/**
 * @file display.c
 * @author MatMasIt
 * @brief Handles displaying of the game
 * @version 0.1
 * @date 2022-03-12
 *
 * @copyright Copyright (c) 2022
 *
 */
/**
 * @brief print the screen matrix
 *
 * @param g Game
 * @param a Arguments
 */
void printScreen(Game *g, args a)
{
    char c;
    bool error;
    if (a.headerShow)
        printf("Generation %" PRIu64 "\n", g->generation);
    for (uint64_t y = 0; y < g->viewRows; y++)
    {
        for (uint64_t x = 0; x < g->viewCols; x++)
        {
            if (getCell(g, x, y, &error) == DEAD)
                c = a.deadc;
            else
                c = a.alivec;
            printf("%c", c);
        }
        printf("\n");
    }
}
