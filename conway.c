/**
 * @file conway.c
 * @author MatMasIt
 * @brief Conway game of life main game functions
 * @version 0.1
 * @date 2022-03-12
 *
 * @copyright Copyright (c) 2022
 *
 */

/**
 * @brief Game struct
 *
 */
typedef struct
{
    uint64_t generation;
    uint64_t rows;
    uint64_t cols;
    uint64_t viewRows;
    uint64_t viewCols;
    bool *data;
} Game;

/**
 * @brief instantiate a new game
 *
 * @param calcRows rows of the calculation matrix
 * @param calcCols cols of the calculation matrix
 * @param viewRows rows of the viewport matrix
 * @param viewCols cols of the viewport matrix
 * @param error error pointer
 * @return Game game struct
 */
Game newGame(uint64_t calcRows, uint64_t calcCols, uint64_t viewRows, uint64_t viewCols, bool *error)
{
    Game g;
    if (viewRows > calcRows || viewCols > calcCols)
    {
        *error = TRUE;
        return g;
    }
    g.generation = 0;
    g.rows = calcRows;
    g.cols = calcCols;
    g.viewRows = viewRows;
    g.viewCols = viewCols;
    g.data = calloc(1, g.rows * g.cols * sizeof(bool));
    if (g.data == NULL)
    {
        *error = TRUE;
        return g;
    }
    *error = FALSE;
    return g;
}
/**
 * @brief Check if coordinates are valid
 *
 * @param g Game
 * @param x x-coord
 * @param y y-cord
 * @return true if valid
 * @return false if not valid
 */
bool checkCoords(Game *g, uint64_t x, uint64_t y)
{
    if (x > g->cols - 1 || y > g->rows - 1)
        return FALSE;
    return TRUE;
}

/**
 * @brief Set a cell's value
 *
 * @param g Game
 * @param x x-coord
 * @param y y-coord
 * @param isAlive aliveness status
 * @return true: success, false: error
 */
bool setCell(Game *g, uint64_t x, uint64_t y, bool isAlive)
{
    if (!checkCoords(g, x, y))
        return FALSE;
    g->data[x + y * g->cols] = isAlive;
    return TRUE;
}
/**
 * @brief Get a cell's valie
 *
 * @param g Game
 * @param x x-coord
 * @param y y-coord
 * @param error error pointer
 * @return true: alive, false: not-alive
 */
bool getCell(Game *g, uint64_t x, uint64_t y, bool *error)
{
    if (!checkCoords(g, x, y))
    {
        *error = TRUE;
        return ALIVE;
    }
    *error = FALSE;
    return g->data[x + y * g->cols];
}
/**
 * @brief Count the number of alive neigbours for a cell
 *
 * @param g Game
 * @param x x-coord
 * @param y y-coord
 * @return int number of alive neigbours
 */
int countLiveNeighbours(Game *g, uint64_t x, uint64_t y)
{
    uint8_t alive = 0;
    bool error = FALSE;
    if (getCell(g, x - 1, y - 1, &error) == ALIVE && !error)
        alive++;
    if (getCell(g, x - 1, y, &error) == ALIVE && !error)
        alive++;
    if (getCell(g, x - 1, y + 1, &error) == ALIVE && !error)
        alive++;

    if (getCell(g, x, y - 1, &error) == ALIVE && !error)
        alive++;
    if (getCell(g, x, y + 1, &error) == ALIVE && !error)
        alive++;

    if (getCell(g, x + 1, y - 1, &error) == ALIVE && !error)
        alive++;
    if (getCell(g, x + 1, y, &error) == ALIVE && !error)
        alive++;
    if (getCell(g, x + 1, y + 1, &error) == ALIVE && !error)
        alive++;
    return alive;
}

/**
 * @brief Progress game by calculating the new matrix and increasing generation
 *
 * @param g Game
 */
void progress(Game *g)
{
    bool error;
    Game c = newGame(g->rows, g->cols, g->viewRows, g->viewCols, &error); // new temp field to apply all rules instantly
    uint8_t liveN;
    bool val;
    memcpy(c.data, g->data, g->rows * g->cols * sizeof(bool));
    c.generation = g->generation + 1;
    for (uint64_t y = 0; y < g->rows; y++)
    {
        for (uint64_t x = 0; x < g->cols; x++)
        {
            val = getCell(g, x, y, &error);
            liveN = countLiveNeighbours(g, x, y);
            if (val == DEAD && liveN == 3)
                setCell(&c, x, y, ALIVE); // Any dead cell with three live neighbours becomes a live cell
            else if (val == ALIVE && (liveN == 2 || liveN == 3))
                setCell(&c, x, y, ALIVE); // Any live cell with two or three live neighbours survives
            else
                setCell(&c, x, y, DEAD); // All other cells either stay dead or die
        }
    }
    free(g->data);
    // copy struct and free previous field
    *g = c;
}
/**
 * @brief Set random population
 *
 * @param g Game
 */
void randomPopulate(Game *g)
{
    srand(time(NULL));
    for (uint64_t y = 0; y < g->rows; y++)
    {
        for (uint64_t x = 0; x < g->cols; x++)
        {
            if (rand() % 2)
                setCell(g, x, y, ALIVE);
            else
                setCell(g, x, y, DEAD);
        }
    }
}
/**
 * @brief Build a game from args struct
 *
 * @param a the args struct
 * @param error error pointer
 * @return Game Game
 */
Game gameFromArgs(args a, bool *error)
{
    Game c = newGame(a.calcRows, a.calcCols, a.viewRows, a.viewCols, error);
    return c;
}