/**
 * @file args.c
 * @author MatMasIt
 * @brief Argument Parsing for the conway Game of Life program
 * @version 0.1
 * @date 2022-03-12
 *
 * @copyright Copyright (c) 2022
 *
 */
// element considered, flags or vals

#define L_VAL 0 // Value
#define L_CAL 2 // --calc rowsxcols
#define T_CAL "--calc"
#define L_VIE 3 // --view rowsxcols
#define T_VIE "--view"
#define L_GEN 4 // --gen
#define T_GEN "--gen"
#define L_NHG 5 // --no-head
#define T_NHG "--no-head"
#define L_DED 6 // --dead-c
#define T_DED "--dead-c"
#define L_ALC 7 // --alive-c
#define T_ALC "--alive-c"
#define L_CEL 9 // --cells
#define T_CEL "--cells"

#define CR 20
#define CC 50
#define VR 20
#define VC 50

#define DEADC '.'
#define ALIVEC '@'

/**
 * @brief struct containing program arguments
 *
 */
typedef struct
{
    uint64_t calcRows;
    uint64_t calcCols;
    // --calc rxc
    uint64_t viewRows;
    uint64_t viewCols;
    // --view rxc
    uint64_t requestedGen; // --gen
    bool headerShow;       // --no-head
    char deadc;            // --dead-c
    char alivec;           // --alive-c
    bool interactive;
    char *cells; // x,y.x,y etc  --cells
} args;
/**
 * @brief parse
 *
 * @param argc argument count
 * @param argv arguments pointer
 * @return args argument struct
 */
args parseArgs(int argc, char **argv)
{
    args a;
    a.calcRows = CR;
    a.calcCols = CC;
    a.viewRows = VR;
    a.viewCols = VC;
    a.interactive = TRUE;
    a.requestedGen = 0;
    a.headerShow = TRUE;
    a.alivec = ALIVEC;
    a.deadc = DEADC;
    a.cells = NULL;
    uint8_t last;
    for (uint8_t i = 0; i < argc; i++)
    {
        char *s = argv[i];
        if (!strcmp(s, T_CAL))
        {
            last = L_CAL;
        }
        else if (!strcmp(s, T_VIE))
        {
            last = L_VIE;
        }
        else if (!strcmp(s, T_GEN))
        {
            last = L_GEN;
        }
        else if (!strcmp(s, T_NHG))
        {
            last = L_VAL;
            a.headerShow = FALSE;
        }
        else if (!strcmp(s, T_DED))
        {
            last = L_DED;
        }
        else if (!strcmp(s, T_ALC))
        {
            last = L_ALC;
        }
        else if (!strcmp(s, T_CEL))
        {
            last = L_CEL;
        }
        else
        {
            switch (last)
            {
            case L_CAL:
                sscanf(s, "%" PRIu64 "x%" PRIu64 "", &a.calcRows, &a.calcCols);
                break;
            case L_VIE:
                sscanf(s, "%" PRIu64 "x%" PRIu64 "", &a.viewRows, &a.viewCols);
                break;
            case L_GEN:
                sscanf(s, "%" PRIu64 "", &a.requestedGen);
                a.interactive = FALSE;
                break;
            case L_DED:
                sscanf(s, "%c", &a.deadc);
                break;
            case L_ALC:
                sscanf(s, "%c", &a.alivec);
                break;
            case L_CEL:
                a.cells = s;
                break;
            }
            last = L_VAL;
        }
    }
    return a;
}
