#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// fukcia C 

char* v(char** array, int* cols) {
    // creating value for caunting
    int col = 1;
    // creating file variable
    FILE* fr2;
    //creating another one dynamic char array == string
    char* filename;
    filename = malloc(sizeof(char) * 128);
    //if dynamic array hasnt beent created yet
    if (array == NULL) {
        //in endless cycle
        while (1) {

            char c = 0;
            //reading from keyboard name of file
            printf("Enter .txt file name\n");
            scanf("%123s", filename);
            //if file opens it reads every single sifn from it
            if (fr2 = fopen(filename, "r")) {
                printf("file was opened\n");
                //moving poiter to the begining of the file
                rewind(fr2);
                //cycle until we will read the EOF== Enf Of File
                while (c != EOF)
                {
                    //output what we got from the file
                    printf("%c", c);
                    //read a sign from file
                    c = fgetc(fr2);
                    //if it finds element of moving to the next lien
                    if (c == '\n') {
                        //make our counter variable bigger
                        ++col;
                    }
                }
                // after previous cycle it breaks out of the endless one
                break;
            }
            else {
                // if file wasnt opened we write this:
                printf("Neotvoreny subor\n");
            }
        }
        // to output few variables of different types it use pointer to one variable of rows 
        *cols = col;
        //returning name of file
        return filename;
    }
    else {
        printf("arrays have already been created\n");
        for (int i = 0; i < *cols; ++i) {
            printf("%s", array[i]);
        }
    }
}
int ch(char filename[], int rows) {//c
//if filename wasnt inputed then go to v function
    if (filename == NULL) {
        printf("Neotvoreny subor\n");
        return 0;
    }
    //Creating dynamic char array  == string in other programmin languages  initialization sizeof 30  char
    char* temp1 = malloc(sizeof(char) * 30);
    //declaration of integer number
    int temp2;
    //declaration of integer number
    float temp3;
    //opening file for reading
    FILE* f = fopen(filename, "rb");
    //reading all lines by types
    for (int i = 0; i < rows; ++i) {
        // first element: ID like integer
        if (!fscanf(f, "%d\n", &temp2)) {
            printf("Nekorektne zadany vstup: ID cislo mer. osoby\n");
            return 0;
        }
        // second element: mer. modul like string. 
        // and other lines with appropriate types too
        if (!fscanf(f, "%s\n", temp1)) {
            printf("Nekorektne zadany vstup: Mer. modul\n");
            return 0;
        }
        if (!fscanf(f, "%s\n", temp1)) {
            printf("Nekorektne zadany vstup: typ. mer veliciny\n");
            return 0;
        }
        if (!fscanf(f, "%f\n", &temp3)) {
            printf("Nekorektne zadany vstup: Hodnota\n");
            return 0;
        }
        if (!fscanf(f, "%d\n", &temp2)) {
            printf("Nekorektne zadany vstup: Cas merania\n");
            return 0;
        }
        if (!fscanf(f, "%d\n", &temp2)) {
            printf("Nekorektne zadany vstup: Datum\n");
            return 0;
        }
    }
    // if it finds something that doesnt fit here it returns 0 as an error
    // else returns 1 as everything is OK
    return 1;
}
//function for creating array of sentences/rows
char** n(char filename[], int rows, int cols) {
    //checking for misstakes in opened file
    if (filename == NULL) {
        printf("Neotvoreny subor.");
        return NULL;
    }
    if (ch(filename, rows) == 0) {
        printf("file contains misstakes\n");
        return 0;
    }
    char c = 0;
    char** names;
    //cating memory for 1st dimension
    names = (char**)malloc(rows * sizeof(char*));

    for (int i = 0; i < rows; i++)
        // allocating memory for 2nd dimension
    {
        names[i] = (char*)malloc(30 * sizeof(char));
    }
    // opening file
    FILE* f = fopen(filename, "r");
    // creating 3 counters
    int i = 0, j = 0, k = 0;
    //reading the file as it was in v fuction
    while (c != EOF && i < rows - 1) {
        c = fgetc(f);
        if (c == '\n') {
            //increasing number of row and decreasing number of element in row to 0
            ++i;
            j = 0;
        }
        //saving in row i and element number j sign c
        names[i][j] = c;
        //going to next sign
        ++j;
    }
    //returning our array
    return names;
}
// sorting by time and date
char** o(char filename[], int rows, int cols, char** arr) {
    if (filename == NULL) {
        printf("Neotvoreny subor.");
        return NULL;
    }
    // creating variable with number of our structers( 7 things in one)
    int arsize = (rows + 1) / 7;
    //creating array of position
    int ar[1000];
    // if array of lines doesnt exist it uses n function
    if (arr == NULL)
        arr = n(filename, rows, cols);
    // filling our positions array
    for (int i = 0; i < arsize; ++i) {
        ar[i] = i;
    }

    // bubble sort method
    for (int i = 0; i < arsize - 1; i++)
        for (int j = 0; j < arsize - i - 1; j++) {
            // cheching which of two dates is bigger
            if (atoi(arr[ar[j] * 7 + 5]) > atoi(arr[ar[j + 1] * 7 + 5])) {
                int temp = ar[j];
                ar[j] = ar[j + 1];
                ar[j + 1] = temp;
                // if they are equal check by time
            }
            else if ((atoi(arr[ar[j] * 7 + 5]) == atoi(arr[ar[j + 1] * 7 + 5])) && (atoi(arr[ar[j] * 7 + 4]) > atoi(arr[ar[j + 1] * 7 + 4]))) {
                int temp = ar[j];
                ar[j] = ar[j + 1];
                ar[j + 1] = temp;
            }
        }
    //creating new array
    char** names;
    //cating memory for 1st dimension
    names = (char**)malloc(rows * sizeof(char*));

    for (int i = 0; i < rows; i++)
        // allocating memory for 2nd dimension
    {
        names[i] = (char*)malloc(30 * sizeof(char));
    }
    // fillning it with elements of first on new positions
    for (int i = 0; i < arsize; ++i) {
        names[i * 7] = arr[ar[i] * 7];
        names[i * 7 + 1] = arr[ar[i] * 7 + 1];
        names[i * 7 + 2] = arr[ar[i] * 7 + 2];
        names[i * 7 + 3] = arr[ar[i] * 7 + 3];
        names[i * 7 + 4] = arr[ar[i] * 7 + 4];
        names[i * 7 + 5] = arr[ar[i] * 7 + 5];
        names[i * 7 + 6] = arr[ar[i] * 7 + 6];
        printf("\n%s", arr[ar[i] * 7 + 1]);
        printf("%s", arr[ar[i] * 7 + 2]);
        printf("%s", arr[ar[i] * 7 + 3]);
        printf("%s", arr[ar[i] * 7 + 4]);
        printf("%s", arr[ar[i] * 7 + 5]);
    }
    // returning sorted array
    return names;
}
// my own function of comparing two lines
int compare(char* s1, char* s2, int m) {
    int NS1 = 0, NS2 = 0;
    // checking if some of lines contains sign of moving to the next lin at the beginig
    if (s1[0] == '\n') {
        NS1++;
    }
    if (s2[0] == '\n') {
        printf("N");
        NS2++;
    }
    // goint through the two lines and checking  if their elements are same
    for (int i = 0; i < m; ++i) {
        // if no return 0
        if (s1[i + NS1] != s2[i + NS2]) {
            return 0;
        }
    }
    // if everything is ok return 1
    return 1;
}
void s(char** array, int rows, int cols, char filename[]) {
    if (filename == NULL) {
        filename = v(array, &rows);
    }
    if (array == NULL) {
        array = n(filename, rows, cols);
    }
    char** A11;
    //reading mer. modul and  typ. mer velecine
    printf("Here Goes mer. modul and typ. mer. velicine:\n");
    A11 = (char**)malloc(2 * sizeof(char*));

    for (int i = 0; i < 2; i++)
        // allocating memory for 2nd dimension
    {
        A11[i] = (char*)malloc(30 * sizeof(char));
        scanf("%s", A11[i]);
    }
    int arsize = (rows + 1) / 7;
    int ArrInt[1000];
    int count = 0;
    // here goes the same thing as in O function
    for (int i = 0; i < arsize; ++i) {
        //  but now it has to leave obly the elements that has the same tyo. mer. velicine and mer. modul 
        if ((compare(array[i * 7 + 1], A11[0], 3) == 1) && (compare(array[i * 7 + 2], A11[1], 2) == 1)) {
            ArrInt[count] = i;
            ++count;
        }
    }
    // bubble sort method
    // same as in o function but with array with fitting positions
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (atoi(array[ArrInt[j] * 7 + 5]) > atoi(array[ArrInt[j + 1] * 7 + 5])) {
                int temp = ArrInt[j];
                ArrInt[j] = ArrInt[j + 1];
                ArrInt[j + 1] = temp;
            }
            else if ((atoi(array[ArrInt[j] * 7 + 5]) == atoi(array[ArrInt[j + 1] * 7 + 5])) && (atoi(array[ArrInt[j] * 7 + 4]) > atoi(array[ArrInt[j + 1] * 7 + 4]))) {
                int temp = ArrInt[j];
                ArrInt[j] = ArrInt[j + 1];
                ArrInt[j + 1] = temp;
            }
        }
    }
    if (count == 0) {
        printf("ANY WASNT FOUND\n");
    }
    else {
        // if it has more than 0 elements it goes to write in file
        FILE* VSTUP;
        //printf("\n%d\n",count);
        VSTUP = fopen("VSTUP_T.txt", "w");
        for (int i = 0; i < count; ++i) {
            fprintf(VSTUP, "\n%s%s%s", array[ArrInt[i] * 7 + 5], array[ArrInt[i] * 7 + 4], array[ArrInt[i] * 7 + 3]);
        }
    }
}// function for intervals
int m(char** array, int rows) {
    if (array == NULL) {
        printf("array wasnt created\n");
        return 0;
    }
    // creating array for every interval
    int gistogram[7];
    for (int i = 0; i < 7; ++i) {
        gistogram[i] = 0;
    }
    char* s;
    s = malloc(sizeof(char) * 2);
    //reading typ. mer. veleciny
    printf("\nwrite Typ. mer. veliciny:\n");
    scanf("%s", s);
    //printf("\n%s",s);
    //and going by 7 in one step and checking every interval
    for (int i = 2; i < rows; i += 7) {
        if (compare(array[i], s, 2) == 1) {
            if (i / 7 <= 5) {
                gistogram[0] += 1;
            }
            else if (i / 7 <= 10) {
                gistogram[1] += 1;
            }
            else if (i / 7 <= 20 && i / 7 > 15) {
                gistogram[2] += 1;
            }
            else if (i / 7 <= 45 && i / 7 > 40) {
                gistogram[3] += 1;
            }
            else if (i / 7 <= 50 && i / 7 > 45) {
                gistogram[4] += 1;
            }
            else if (i / 7 <= 55 && i / 7 > 50) {
                gistogram[5] += 1;
            }
            else if (i / 7 <= 155 && i / 7 > 150) {
                gistogram[6] += 1;
            }
        }
    }
    //outputing value of every interval
    printf("\n(  0.0 -   5.0>   %d", gistogram[0]);
    printf("\n(  5.0 -  10.0>   %d", gistogram[1]);
    printf("\n( 15.0 -  20.0>   %d", gistogram[2]);
    printf("\n( 40.0 -  45.0>   %d", gistogram[3]);
    printf("\n( 45.0 -  50.0>   %d", gistogram[4]);
    printf("\n( 50.0 -  55.0>   %d", gistogram[5]);
    printf("\n(150.0 - 155.0>   %d\n", gistogram[6]);

}
void r(char filename[], int rows, int cols) {
    char** array = NULL;
    if (filename == NULL) {
        filename = v(array, &rows);
    }
    // creating sorted array with O function
    array = o(filename, rows, cols, array);
    //first element output with normal type
    printf("\n\n%c%c : %c%c", array[4][1], array[4][2], array[4][3], array[4][4]);
    for (int i = 11; i < rows; i += 7) {
        // checking every next element of time((  checking if previous time has the sime hour 
        if ((array[i][1] == array[i - 7][1] || array[i - 7][2] == array[i][2]) && (array[i - 7][3] != array[i][3] || array[i - 7][4] != array[i][4])) {
            printf(",%c%c", array[i][3], array[i][4]);
        }
        //if not write as normal
        else if (array[i - 7][3] != array[i][3] || array[i - 7][4] != array[i][4]) {
            printf("\n%c%c : %c%c", array[i][1], array[i][2], array[i][3], array[i][4]);
        }
    }
}
//function for deleting elements by ID
char** z(char** array, int rows, int* retur) {
    if (array == NULL) {
        printf("dynamic arrays wasnt intialized\n");
        return array;
    }
    char** names;
    char* s;
    s = malloc(sizeof(char) * 10);
    int count = 0;
    //reading id
    printf("write ID:\n");
    scanf("%s", s);
    //counting elements with this id
    for (int i = 0; i < rows; i += 7) {
        if (compare(array[i], s, 10) == 1) {
            ++count;
        }
    }
    printf("\n\nDeleted: %d\n\n", count);
    //cating array with less elements
    //cating memory for 1st dimension
    names = (char**)malloc((rows + 1 - count * 7) * sizeof(char*));
    for (int i = 0; i < count; i++)
        // allocating memory for 2nd dimension
    {
        names[i] = (char*)malloc(30 * sizeof(char));
    }
    //coping our ellements from first one to second one
    int i = 0, j = 0;
    while (i < rows) {
        // if it has the same id, going to next group of elements by skiping this 7
        if (compare(array[i], s, 10) == 1) {
            i += 7;
        }
        else {
            names[j] = array[i];
            ++i;
            ++j;
        }
    }
    // returning number of rows using pointers
    int temp = rows - count * 7;
    *retur = temp;
    //returning new array
    return names;

}
void h(char** array, int rows) {

    char** times;
    times = (char**)malloc(sizeof(char*) * ((rows + 1) / 7));
    for (int i = 0; i < (rows + 1) / 7; i++) {
        times[i] = (char*)malloc(sizeof(char) * 10);
    }
    for (int i = 4; i < rows; i = i + 7) {
        times[i / 7] = array[i];
    }

    int count = (rows + 1) / 7;
    char* help;
    help = malloc(sizeof(char) * 10);

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (atoi(times[j]) > atoi(times[j + 1])) {
                help = "";
                help = times[j];
                times[j] = times[j + 1];
                times[j + 1] = help;
            }
        }
    }

    int* counters;
    counters = malloc(sizeof(int) * count);

    for (int i = 0; i < count; ++i) {
        counters[i] = 0;
    }

    counters[0] = 1;
    int co = 0;

    for (int i = 1; i < count; i++) {
        if (compare(times[i - 1], times[i], 5) != 1) {
            co++;
        }
        counters[co]++;
    }
    int pos = 0;
    for (int i = 1; i < count; i++) {
        if (counters[pos] > 0 && (compare(times[i - 1], times[i], 5) == 0)) {
            printf("%s\n", times[i]);
            printf("- %3d\n", counters[pos]);
            pos++;
        }
    }
}
void j(char** array, int rows) {
    int* counters;
    counters = malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; ++i) {
        counters[i] = 0;
    }
    int k;
    printf("\nwrite k:\n");
    scanf("%d", &k);
    if (k > 0) {
        for (int i = 0; i < rows; i = i + 7 * k) {
            for (int j = 0; j <= 10; ++j) {
                switch (array[i][j]) {
                case '0': {
                    counters[0] ++;
                    break;
                }
                case '1': {
                    counters[1] ++;
                    break;
                }
                case '2': {
                    counters[2] ++;
                    break;
                }
                case '3': {
                    counters[3] ++;
                    break;
                }
                case '4': {
                    counters[4] ++;
                    break;
                }
                case '5': {
                    counters[5] ++;
                    break;
                }
                case '6': {
                    counters[6] ++;
                    break;
                }
                case '7': {
                    counters[7] ++;
                    break;
                }
                case '8': {
                    counters[8] ++;
                    break;
                }
                case '9': {
                    counters[9] ++;
                    break;
                }
                }
            }
        }
        for (int i = 0; i < 10; ++i) {
            if (counters[i] > 0) {
                printf("%3d ", i);
            }
        }
        printf("\n");
        for (int i = 0; i < 10; ++i) {
            if (counters[i] > 0) {
                printf("%3d ", counters[i]);
            }
        }
    }
}
int main()
{
    char** names;
    names = NULL;
    char* filename;
    filename = malloc(sizeof(char) * 128);
    int rows = 0;
    filename = NULL;

    //endless cycle
    while (1) {
        //read commands by letters
        char c;
        scanf("%c", &c);
        // in case of every letter it calls fitting function
        switch (c) {
        case 'v': {
            filename = v(names, &rows);
            break;
        }
        case 'o': {
            names = o(filename, rows, 7, names);
            break;
        }
        case 'n': {
            names = n(filename, rows, 7);
            break;
        }
        case 'c': {
            if (ch(filename, rows) == 0) {
                printf("file contains misstakes\n");
            }
            else {
                printf("file doesnt contain misstakes\n");
            }

            break;
        }
        case 's': {
            s(names, rows, 7, filename);
            break;
        }
        case 'm': {
            m(names, rows);
            break;
        }
        case 'r': {
            r(filename, rows, 7);
            break;
        }
        case 'z': {
            names = z(names, rows, &rows);
            break;
        }case 'j': {
            j(names, rows);
            break;
        }case 'h': {
            h(names, rows);
            break;
        }
        case 'k': {
            //free(deallocating) allocated memory and ending program
            free(names);
            return 0;
        }
        }
    }
    return 0;
}