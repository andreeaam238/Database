/* Blaga Ana-Maria-Andreea, 314CB */

#include "structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definire a doua operatii posibile in functiile COMPARE_INT, COMPARE_FLOAT, COMPARE_STRING.

#define SEARCH_LINE 0
#define DELETE_LINE 1

// Functie pentru initializarea unei baze de date.

// Returneaza adresa de memorie a bazei de date sau NULL in cazul in care
// initializarea esueaza.

t_db *INIT_DB(char *name) {
  t_db *DB = (t_db *)calloc(1, sizeof(t_db));
  if (!DB) {
    return NULL;
  }
  strcpy(DB->name, name);
  DB->tables = NULL;
  return DB;
}

// Functie care creeaza un tabel intr-o baza de date existenta.

// Returneaza 0 in cazul in care crearea reuseste, 1 cand aceasta esueaza.

int CREATE(t_db *DB, char *name, char *type, char *columns) {
  t_table *table = DB->tables, *prev_table = NULL;

  while (table != NULL) {
    if (strcmp(table->name, name) == 0) {
      printf("Table %s already exists.\n", name);
      return 1;
    }
    prev_table = table;
    table = table->next;
  }

  table = (t_table *)calloc(1, sizeof(t_table));
  if (!table) {
    return 1;
  }

  strcpy(table->name, name);

  if (strcmp("INT", type) == 0) {
    table->type = INT;
  } else if (strcmp("FLOAT", type) == 0) {
    table->type = FLOAT;
  } else if (strcmp("STRING", type) == 0) {
    table->type = STRING;
  } else {
    printf("Unknown data type: %s", type);
    free(table);
    return 1;
  }

  char *col_name = strtok(columns, " ");

  while (col_name != NULL) {
    t_column *col = (t_column *)calloc(1, sizeof(t_column)), *prev_col;
    if (!col) {
      return 1;
    }

    if (table->columns == NULL) {
      table->columns = col;
    } else {
      prev_col->next = col;
      col->next = NULL;
    }

    prev_col = col;
    strcpy(col->name, col_name);
    col_name = strtok(NULL, " ");
  }

  if (prev_table == NULL) {
    DB->tables = table;
  } else {
    prev_table->next = table;
  }

  table->next = NULL;

  return 0;
}

// Functie care adauga intr-un tabel precizat, al carui tip este INT, o
// inregistrare(o linie cu date).

// Returneaza 1 in cazul adaugarii reusite, iar in caz contrar 0.

int ADD_INT(char *data, t_table *table) {
  t_intLine *line = (t_intLine *)calloc(1, sizeof(t_intLine));

  if (!line) {
    return 1;
  }

  char *elem = strtok(data, " ");
  t_intCell *prev_cell = NULL;
  line->next = NULL;

  while (elem != NULL) {
    t_intCell *cell = (t_intCell *)calloc(1, sizeof(t_intCell));

    if (!cell) {
      free(line);
      return 1;
    }

    int cmp_val;
    sscanf(elem, "%d", &cmp_val);
    cell->value = cmp_val;
    cell->next = NULL;

    if (prev_cell == NULL) {
      line->cells = cell;
    } else {
      prev_cell->next = cell;
    }

    prev_cell = cell;
    elem = strtok(NULL, " ");
  }

  if ((t_intLine *)(table->lines) == NULL) {
    table->lines = (void *)line;
  } else {
    t_intLine *current_line = (t_intLine *)(table->lines), *prev_line;

    while (current_line != NULL) {
      prev_line = current_line;
      current_line = current_line->next;
    }

    prev_line->next = line;
  }
  return 0;
}

// Functie care adauga intr-un tabel precizat, al carui tip este FLOAT, o
// inregistrare(o linie cu date).

// Returneaza 1 in cazul adaugarii reusite, iar in caz contrar 0.

int ADD_FLOAT(char *data, t_table *table) {
  t_floatLine *line = (t_floatLine *)calloc(1, sizeof(t_floatLine));

  if (!line) {
    return 1;
  }

  char *elem = strtok(data, " ");
  t_floatCell *prev_cell = NULL;
  line->next = NULL;

  while (elem != NULL) {
    t_floatCell *cell = (t_floatCell *)calloc(1, sizeof(t_floatCell));

    if (!cell) {
      free(line);
      return 1;
    }

    float cmp_val;
    sscanf(elem, "%f", &cmp_val);
    cell->value = cmp_val;
    cell->next = NULL;

    if (prev_cell == NULL) {
      line->cells = cell;
    } else {
      prev_cell->next = cell;
    }

    prev_cell = cell;
    elem = strtok(NULL, " ");
  }

  if ((t_intLine *)(table->lines) == NULL) {
    table->lines = (void *)line;
  } else {
    t_floatLine *current_line = (t_floatLine *)(table->lines), *prev_line;

    while (current_line != NULL) {
      prev_line = current_line;
      current_line = current_line->next;
    }

    prev_line->next = line;
  }
  return 0;
}

// Functie care adauga intr-un tabel precizat, al carui tip este STRING, o
// inregistrare(o linie cu date).

// Returneaza 1 in cazul adaugarii reusite, iar in caz contrar 0.

int ADD_STRING(char *data, t_table *table) {
  t_stringLine *line = (t_stringLine *)calloc(1, sizeof(t_stringLine));

  if (!line) {
    return 0;
  }

  char *elem = strtok(data, " ");
  t_stringCell *prev_cell = NULL;
  line->next = NULL;

  while (elem != NULL) {
    t_stringCell *cell = (t_stringCell *)calloc(1, sizeof(t_stringCell));

    if (!cell) {
      free(line);
      return 1;
    }

    cell->value = strdup(elem);
    if (!cell->value) {
      free(cell);
      free(line);
      return 1;
    }
    cell->next = NULL;

    if (prev_cell == NULL) {
      line->cells = cell;
    } else {
      prev_cell->next = cell;
    }

    prev_cell = cell;
    elem = strtok(NULL, " ");
  }

  if ((t_stringLine *)(table->lines) == NULL) {
    table->lines = (void *)line;
  } else {
    t_stringLine *current_line = (t_stringLine *)(table->lines), *prev_line;

    while (current_line != NULL) {
      prev_line = current_line;
      current_line = current_line->next;
    }

    prev_line->next = line;
  }
  return 0;
}

// Functia adauga intr-un tabel precizat o inregistrare(o linie cu date).

// In functie de tipul tabelului sunt apelate functii specializate pentru
// fiecare dintre acestea:ADD_INT, ADD_FLOAT si ADD_STRING.

// Returneaza 0 in cazul adaugarii reusite, iar 1 in caz contrar.

// In situatia in care tabelul nu exista se afiseaza un mesaj de eroare
// si se returneaza 1.

int ADD(t_db *DB, char *table_name, char *data) {
  t_table *table = DB->tables;
  int res;

  while (table != NULL) {
    if (strcmp(table->name, table_name) == 0) {
      if (table->type == INT) {
        res = ADD_INT(data, table);
      } else if (table->type == FLOAT) {
        res = ADD_FLOAT(data, table);
      } else if (table->type == STRING) {
        res = ADD_STRING(data, table);
      }
      return res;
    }

    table = table->next;
  }
  printf("Table \"%s\" not found in database.\n", table_name);
  return 1;
}

// Functie care afiseaza capul de tabel al unui tabel precizat.

// Este afisat mai intai numele tabelului, iar pe randul urmator sunt afisate
// numele coloanelor.

void PRINT_TABLE_INFO(t_table *table) {
  printf("TABLE: %s\n", table->name);

  t_column *col = table->columns;

  while (col != NULL) {
    printf("%-30s ", col->name);
    col = col->next;
  }
  printf("\n");

  char separator[] = "------------------------------";
  col = table->columns;

  while (col != NULL) {
    printf("%s ", separator);
    col = col->next;
  }
  printf("\n");
}

// Functia afiseaza o inregistrare(o linie cu date) de tip INT.

void PRINT_INT_LINE(t_intLine *line) {
  t_intCell *cell = line->cells;

  while (cell != NULL) {
    printf("%-30d ", cell->value);
    cell = cell->next;
  }
  printf("\n");
}

// Functia afiseaza inregistrarile(liniile cu date) dintr-un tabel precizat, al
// carui tip este INT.

void PRINT_INT(t_table *table) {
  t_intLine *line = (t_intLine *)(table->lines);

  while (line != NULL) {
    PRINT_INT_LINE(line);
    line = line->next;
  }
}

// Functia afiseaza o inregistrare(o linie cu date) de tip FLOAT.

void PRINT_FLOAT_LINE(t_floatLine *line) {
  t_floatCell *cell = line->cells;

  while (cell != NULL) {
    printf("%-30f ", cell->value);
    cell = cell->next;
  }
  printf("\n");
}

// Functia afiseaza inregistrarile(liniile cu date) dintr-un tabel precizat, al
// carui tip este FLOAT.

void PRINT_FLOAT(t_table *table) {
  t_floatLine *line = (t_floatLine *)(table->lines);

  while (line != NULL) {
    PRINT_FLOAT_LINE(line);
    line = line->next;
  }
}

// Functia afiseaza o inregistrare(o linie cu date) de tip STRING.

void PRINT_STRING_LINE(t_stringLine *line) {
  t_stringCell *cell = line->cells;

  while (cell != NULL) {
    printf("%-30s ", cell->value);
    cell = cell->next;
  }
  printf("\n");
}

// Functia afiseaza inregistrarile(liniile cu date) dintr-un tabel precizat, al
// carui tip este STRING.

void PRINT_STRING(t_table *table) {
  t_stringLine *line = (t_stringLine *)(table->lines);

  while (line != NULL) {
    PRINT_STRING_LINE(line);
    line = line->next;
  }
}

// Functia afiseaza continutul unui tabel precizat.

// In functie de tipul tabelului sunt apelate functii specializate pentru
// fiecare dintre acestea:PRINT_INT, PRINT_FLOAT si PRINT_STRING.

// In cazul in care tabelul nu exista in baza de date se afiseaza un mesaj de
// eroare.

void PRINT(t_db *DB, char *table_name) {
  t_table *table = DB->tables;

  while (table != NULL) {
    if (strcmp(table->name, table_name) == 0) {
      PRINT_TABLE_INFO(table);

      if (table->type == INT) {
        PRINT_INT(table);
      } else if (table->type == FLOAT) {
        PRINT_FLOAT(table);
      } else {
        PRINT_STRING(table);
      }
      printf("\n");

      break;
    }
    table = table->next;
  }
  if (table == NULL) {
    printf("Table \"%s\" not found in database.\n", table_name);
  }
}

// Functia elibereaza memoria alocata fiecarei celule de tip INT dintr-o linie
// de acelasi tip.

void DELETE_INT_LINE(t_intLine *line) {
  t_intCell *cell = line->cells;

  while (cell != NULL) {
    t_intCell *aux_cell = cell;
    cell = cell->next;
    free(aux_cell);
  }
}

// Functia compara valorile din celulele aflate in a col_ind coloana din fiecare
// linie a unui tabel de tip INT precizat cu o valoare de referinta(cmp_val),
// folosind o relatie precizata(rel).

// Functia primeste ca parametru variabila op care defineste operatia ce se va
// efectua in cazul in care relatia este adevarata, astfel:
// 0 - SEARCH_LINE - afiseaza linia respectiva
// 1 - DELETE_LINE - elimina din tabel linia respectiva

void COMPARE_INT(t_table *table, char *rel, char *val, int col_ind, int op) {
  t_intLine *line = (t_intLine *)(table->lines), *prev_line = NULL;

  int cmp_val;
  sscanf(val, "%d", &cmp_val);

  while (line != NULL) {
    int is_line_ok_for_cmp = 0, i;
    t_intCell *cell = line->cells;

    for (i = 0; i < col_ind; i++) {
      cell = cell->next;
    }

    if (strcmp(rel, "<") == 0 && cell->value < cmp_val) {
      is_line_ok_for_cmp = 1;
    } else if (strcmp(rel, "<=") == 0 && cell->value <= cmp_val) {
      is_line_ok_for_cmp = 1;
    } else if (strcmp(rel, "==") == 0 && cell->value == cmp_val) {
      is_line_ok_for_cmp = 1;
    } else if (strcmp(rel, "!=") == 0 && cell->value != cmp_val) {
      is_line_ok_for_cmp = 1;
    } else if (strcmp(rel, ">=") == 0 && cell->value >= cmp_val) {
      is_line_ok_for_cmp = 1;
    } else if (strcmp(rel, ">") == 0 && cell->value > cmp_val) {
      is_line_ok_for_cmp = 1;
    }

    if (op == SEARCH_LINE) {
      if (is_line_ok_for_cmp == 1) {
        PRINT_INT_LINE(line);
      }
      line = line->next;
    } else if (op == DELETE_LINE) {
      if (is_line_ok_for_cmp == 1) {
        DELETE_INT_LINE(line);

        if (prev_line == NULL) {
          table->lines = line->next;
        } else {
          prev_line->next = line->next;
        }

        t_intLine *aux_line = line;
        line = line->next;
        free(aux_line);

      } else {
        prev_line = line;
        line = line->next;
      }
    }
  }
  if (op == SEARCH_LINE) {
    printf("\n");
  }
}

// Functia elibereaza memoria alocata fiecarei celule de tip FLOAT dintr-o linie
// de acelasi tip.

void DELETE_FLOAT_LINE(t_floatLine *line) {
  t_floatCell *cell = line->cells;

  while (cell != NULL) {
    t_floatCell *aux_cell = cell;
    cell = cell->next;
    free(aux_cell);
  }
}

// Functia compara valorile din celulele aflate in a col_ind coloana din fiecare
// linie a unui tabel de tip FLOAT precizat cu o valoare de referinta(cmp_val),
// folosind o relatie precizata(rel).

// Functia primeste ca parametru variabila op care defineste operatia ce se va
// efectua in cazul in care relatia este adevarata, astfel:
// 0 - SEARCH_LINE - afiseaza linia respectiva
// 1 - DELETE_LINE - elimina din tabel linia respectiva

void COMPARE_FLOAT(t_table *table, char *rel, char *val, int col_ind, int op) {
  t_floatLine *line = (t_floatLine *)(table->lines), *prev_line = NULL;
  float cmp_val;
  sscanf(val, "%f", &cmp_val);

  while (line != NULL) {
    int is_line_ok = 0, i;
    t_floatCell *cell = line->cells;

    for (i = 0; i < col_ind; i++) {
      cell = cell->next;
    }

    if (strcmp(rel, "<") == 0 && cell->value < cmp_val) {
      is_line_ok = 1;
    } else if (strcmp(rel, "<=") == 0 && cell->value <= cmp_val) {
      is_line_ok = 1;
    } else if (strcmp(rel, "==") == 0 && cell->value == cmp_val) {
      is_line_ok = 1;
    } else if (strcmp(rel, "!=") == 0 && cell->value != cmp_val) {
      is_line_ok = 1;
    } else if (strcmp(rel, ">=") == 0 && cell->value >= cmp_val) {
      is_line_ok = 1;
    } else if (strcmp(rel, ">") == 0 && cell->value > cmp_val) {
      is_line_ok = 1;
    }

    if (op == SEARCH_LINE) {
      if (is_line_ok == 1) {
        PRINT_FLOAT_LINE(line);
      }
      line = line->next;
    } else if (op == DELETE_LINE) {
      if (is_line_ok == 1) {
        DELETE_FLOAT_LINE(line);

        if (prev_line == NULL) {
          table->lines = line->next;
        } else {
          prev_line->next = line->next;
        }

        t_floatLine *aux_line = line;
        line = line->next;
        free(aux_line);

      } else {
        prev_line = line;
        line = line->next;
      }
    }
  }
  if (op == SEARCH_LINE) {
    printf("\n");
  }
}
// Functia elibereaza memoria alocata fiecarei celule de tip STRING dintr-o
// linie de acelasi tip, cat si memoria alocata pentru fiecare valoare din
// celule.

void DELETE_STRING_LINE(t_stringLine *line) {
  t_stringCell *cell = line->cells;

  while (cell != NULL) {
    t_stringCell *aux_cell = cell;
    cell = cell->next;
    free(aux_cell->value);
    free(aux_cell);
  }
}

// Functia compara valorile din celulele aflate in a col_ind coloana din fiecare
// linie a unui tabel de tip STRING precizat cu o valoare de referinta(cmp_val),
// folosind o relatie precizata(rel).

// Functia primeste ca parametru variabila op care defineste operatia ce se va
// efectua in cazul in care relatia este adevarata, astfel:
// 0 - SEARCH_LINE - afiseaza linia respectiva
// 1 - DELETE_LINE - elimina din tabel linia respectiva

void COMPARE_STRING(t_table *table, char *rel, char *val, int col_ind, int op) {
  t_stringLine *line = (t_stringLine *)(table->lines), *prev_line = NULL;

  while (line != NULL) {
    int is_line_ok = 0, i;
    t_stringCell *cell = line->cells;

    for (i = 0; i < col_ind; i++) {
      cell = cell->next;
    }

    int cmp = strcmp(cell->value, val);

    if (strcmp(rel, "<") == 0 && cmp < 0) {
      is_line_ok = 1;
    } else if (strcmp(rel, "<=") == 0 && cmp <= 0) {
      is_line_ok = 1;
    } else if (strcmp(rel, "==") == 0 && cmp == 0) {
      is_line_ok = 1;
    } else if (strcmp(rel, "!=") == 0 && cmp != 0) {
      is_line_ok = 1;
    } else if (strcmp(rel, ">=") == 0 && cmp >= 0) {
      is_line_ok = 1;
    } else if (strcmp(rel, ">") == 0 && cmp > 0) {
      is_line_ok = 1;
    }

    if (op == SEARCH_LINE) {
      if (is_line_ok == 1) {
        PRINT_STRING_LINE(line);
      }
      line = line->next;
    } else if (op == DELETE_LINE) {
      if (is_line_ok == 1) {
        DELETE_STRING_LINE(line);

        if (prev_line == NULL) {
          table->lines = line->next;
        } else {
          prev_line->next = line->next;
        }

        t_stringLine *aux_line = line;
        line = line->next;
        free(aux_line);

      } else {
        prev_line = line;
        line = line->next;
      }
    }
  }
  if (op == SEARCH_LINE) {
    printf("\n");
  }
}

// Functia cauta intr-o baza de date un tabel precizat, iar in cazul in care
// acesta nu exista este afisat un mesaj de eroare.

// Apoi este cautata in acesta o coloana precizata, iar in cazul in care
// aceasta nu exista se afiseaza un mesaj de eroare.

// Este afisat capul de tabel in cazul in care coloana respectiva se afla in
// tabel, iar apoi sunt afisate liniile care indeplinesc o anumita conditie
// folosind functii specializate pentru tipul tabelului: COMPARE_INT,
// COMPARE_FLOAT, COMPARE_STRING.

void SEARCH(t_db *DB, char *table_name, char *col_name, char *rel, char *val) {
  if (DB) {
    t_table *table = DB->tables;

    while (table != NULL) {
      if (strcmp(table->name, table_name) == 0) {
        t_column *col = table->columns;
        int col_ind = 0;

        while (col != NULL && strcmp(col->name, col_name) != 0) {
          col = col->next;
          col_ind++;
        }

        if (col != NULL) {
          PRINT_TABLE_INFO(table);
          if (table->type == INT) {
            COMPARE_INT(table, rel, val, col_ind, SEARCH_LINE);
          } else if (table->type == FLOAT) {
            COMPARE_FLOAT(table, rel, val, col_ind, SEARCH_LINE);
          } else if (table->type == STRING) {
            COMPARE_STRING(table, rel, val, col_ind, SEARCH_LINE);
          }
        } else {
          printf("Table \"%s\" does not contain column \"%s\".\n", table_name,
                 col_name);
          break;
        }
        break;
      }
      table = table->next;
    }
    if (table == NULL) {
      printf("Table \"%s\" not found in database.\n", table_name);
    }
  }
}

// Functia cauta intr-o baza de date un tabel precizat, iar in cazul in care
// acesta nu exista este afisat un mesaj de eroare.

// Apoi este cautata in acesta o coloana precizata, iar in cazul in care
// aceasta nu exista se afiseaza un mesaj de eroare.

// Sunt sterse liniile care indeplinesc o anumita conditie folosind functii 
// specializate pentru tipul tabelului: COMPARE_INT, COMPARE_FLOAT, 
// COMPARE_STRING.

void DELETE(t_db *DB, char *table_name, char *col_name, char *rel, char *val) {
  t_table *table = DB->tables;

  while (table != NULL) {
    if (strcmp(table->name, table_name) == 0) {
      t_column *col = table->columns;
      int col_ind = 0;

      while (col != NULL && strcmp(col->name, col_name) != 0) {
        col = col->next;
        col_ind++;
      }

      if (col != NULL) {
        if (table->type == INT) {
          COMPARE_INT(table, rel, val, col_ind, DELETE_LINE);
        } else if (table->type == FLOAT) {
          COMPARE_FLOAT(table, rel, val, col_ind, DELETE_LINE);
        } else if (table->type == STRING) {
          COMPARE_STRING(table, rel, val, col_ind, DELETE_LINE);
        }
      } else {
        printf("Table \"%s\" does not contain column \"%s\".\n", table_name,
               col_name);
        break;
      }

      break;
    }
    table = table->next;
  }
  if (table == NULL) {
    printf("Table \"%s\" not found in database.\n", table_name);
  }
}

// Functia elimina toate liniile dintr-un tabel de tip INT.

void CLEAR_INT(t_intLine **line) {
  t_intLine *line_ptr = *line, *aux_line;

  while (line_ptr != NULL) {
    DELETE_INT_LINE(line_ptr);

    aux_line = line_ptr;
    line_ptr = line_ptr->next;
    free(aux_line);
  }

  *line = NULL;
}

// Functia elimina toate liniile dintr-un tabel de tip FLOAT.

void CLEAR_FLOAT(t_floatLine **line) {
  t_floatLine *line_ptr = *line, *aux_line;

  while (line_ptr != NULL) {
    DELETE_FLOAT_LINE(line_ptr);

    aux_line = line_ptr;
    line_ptr = line_ptr->next;
    free(aux_line);
  }

  *line = NULL;
}

// Functia elimina toate liniile dintr-un tabel de tip STRING.

void CLEAR_STRING(t_stringLine **line) {
  t_stringLine *line_ptr = *line, *aux_line;

  while (line_ptr != NULL) {
    DELETE_STRING_LINE(line_ptr);

    aux_line = line_ptr;
    line_ptr = line_ptr->next;
    free(aux_line);
  }

  *line = NULL;
}

// Functia cauta un tabel precizat intr-o baza de date, iar in cazul in care
// acesta nu exista este afisat un mesaj de eroare.

// In cazul in care acesta exista sunt eliminate toate liniile din tabel
// folosind functii specializate pentru tipul tabelului: CLEAR_INT, CLEAR_FLOAT,
// CLEAR_STRING.

void CLEAR(t_db *DB, char *table_name) {
  t_table *table = DB->tables;

  while (table != NULL) {
    if (strcmp(table->name, table_name) == 0) {

      if (table->type == INT) {
        t_intLine *line = (t_intLine *)table->lines;
        CLEAR_INT(&line);
      } else if (table->type == FLOAT) {
        t_floatLine *line = (t_floatLine *)table->lines;
        CLEAR_FLOAT(&line);
      } else {
        t_stringLine *line = (t_stringLine *)table->lines;
        CLEAR_STRING(&line);
      }

      table->lines = NULL;

      break;
    }
    table = table->next;
  }
  if (table == NULL) {
    printf("Table \"%s\" not found in database.\n", table_name);
  }
}

// Functie care elibereaza memoria capului de tabel.

void DELETE_TABLE_INFO(t_table *table) {
  t_column *col = table->columns;

  while (col != NULL) {
    t_column *aux_col = col;
    col = col->next;
    free(aux_col);
  }

  table->columns = NULL;
}

// Functie care cauta un tabel precizat intr-o baza de date, iar in cazul in
// care acesta nu exista este afisat un mesaj de eroare.

// In cazul in care acesta exista este eliberata memoria capuilui de tabel
// folosind functia: DELETE_TABLE_INFO.

// Apoi este eliminata memoria pentru liniile tabelului folosind functii
// specilizate pentru tipul de tabel: CLEAR_INT, CLEAR_FLOAT, CLEAR_STRING.

void DELETE_TABLE(t_db *DB, char *table_name) {
  t_table *table = DB->tables, *prev_table = NULL;

  while (table != NULL) {
    if (strcmp(table->name, table_name) == 0) {
      DELETE_TABLE_INFO(table);

      if (table->type == INT) {
        t_intLine *line = (t_intLine *)table->lines;
        CLEAR_INT(&line);
      } else if (table->type == FLOAT) {
        t_floatLine *line = (t_floatLine *)table->lines;
        CLEAR_FLOAT(&line);
      } else {
        t_stringLine *line = (t_stringLine *)table->lines;
        CLEAR_STRING(&line);
      }

      table->lines = NULL;

      t_table *aux_table;
      if (prev_table == NULL) {
        aux_table = DB->tables;
        DB->tables = aux_table->next;
        free(aux_table);
      } else {
        aux_table = table;
        prev_table->next = table->next;
        free(aux_table);
      }

      break;
    }
    prev_table = table;
    table = table->next;
  }
  if (table == NULL) {
    printf("Table \"%s\" not found in database.\n", table_name);
  }
}

// Functie pentru eliberarea memoriei ocupate de o baza de date.

// Pentru fiecare tabel este eliberata memoria pentru capul de tabel si apoi
// liniile acestuia folosind functii specializate in functie de tipul tabelului:
// CLEAR_INT, CLEAR_FLOAT, CLEAR_STRING.

// Apoi este eliberata memoria ocupata de fiecare tabel, iar in final cea
// ocupata de baza de date.

void DELETE_DB(t_db **DB) {
  if (DB) {
    t_table *table = (*DB)->tables;

    while (table != NULL) {
      DELETE_TABLE_INFO(table);

      if (table->type == INT) {
        t_intLine *line = (t_intLine *)table->lines;
        CLEAR_INT(&line);
      } else if (table->type == FLOAT) {
        t_floatLine *line = (t_floatLine *)table->lines;
        CLEAR_FLOAT(&line);
      } else {
        t_stringLine *line = (t_stringLine *)table->lines;
        CLEAR_STRING(&line);
      }

      table->lines = NULL;

      t_table *aux = table;
      table = table->next;
      free(aux);
    }

    free(*DB);
    *DB = NULL;
  }
}

// Functie care afiseaza continutul unei baze de date.

// Este afisat numele bazei de date, apoi numele tabelelor, capetele de tabel si
// continutul fiecaruia folosind functii specializate: PRINT_INT, PTRINT_FLOAT,
// PRINT_STRING.

void PRINT_DB(t_db *DB) {
  if (DB) {
    t_table *table = DB->tables;
    printf("DATABASE: %s\n\n", DB->name);
    while (table != NULL) {
      PRINT_TABLE_INFO(table);
      if (table->lines != NULL) {
        if (table->type == INT) {
          PRINT_INT(table);
        } else if (table->type == FLOAT) {
          PRINT_FLOAT(table);
        } else {
          PRINT_STRING(table);
        }
      }
      printf("\n");
      table = table->next;
    }
  }
}

// Functia main

int main() {
  int end = 1;
  t_db *DB = NULL;

  // Meniul

  while (end != 0) {

    // Se citeste comanda.

    char *cmd = calloc(MAX_CMD_LEN, sizeof(char)), *ptr, *cmd_cpy = calloc(MAX_CMD_LEN, sizeof(char));
    if (!cmd) {
      if (DB) {
        DELETE_DB(&DB);
      }
      return 1;
    }

    if (!cmd_cpy) {
      if (DB) {
        DELETE_DB(&DB);
      }
      free(cmd);
      return 1;
    }

    fgets(cmd, MAX_CMD_LEN, stdin);
    cmd[strlen(cmd) - 1] = '\0';
    strcpy(cmd_cpy, cmd);
    ptr = strtok(cmd, " ");

    // Se selecteaza operatia dorita.

    // Initializarea bazei de date.

    if (strcmp(ptr, "INIT_DB") == 0) {
      ptr = strtok(NULL, " ");
      DB = INIT_DB(ptr);
      if (!DB) {
        free(cmd);
        free(cmd_cpy);
        return 1;
      }
    }

    // Crearea unui tabel in baza de date existenta.

    else if (strcmp(ptr, "CREATE") == 0) {
      char *table_name, *type, *columns = calloc(MAX_CMD_LEN, sizeof(char));
      if (!columns) {
        free(cmd);
        free(cmd_cpy);
        if (DB) {
          DELETE_DB(&DB);
        }
        return 1;
      }

      ptr = strtok(NULL, " ");
      table_name = strdup(ptr);
      if (!table_name) {
        free(columns);
        free(cmd);
        free(cmd_cpy);
        if (DB) {
          DELETE_DB(&DB);
        }
        return 1;
      }

      ptr = strtok(NULL, " ");
      type = strdup(ptr);
      if (!type) {
        free(columns);
        free(cmd);
        free(cmd_cpy);
        free(table_name);
        if (DB) {
          DELETE_DB(&DB);
        }
        return 1;
      }

      ptr = strtok(NULL, " ");
      while (ptr != NULL) {
        strcat(columns, ptr);
        ptr = strtok(NULL, " ");
        if (ptr != NULL) {
          strcat(columns, " ");
        }
      }
      CREATE(DB, table_name, type, columns);

      free(columns);
      free(type);
      free(table_name);
    }

    // Afisarea continutului bazei de date.

    else if (strcmp(ptr, "PRINT_DB") == 0) {
      PRINT_DB(DB);
    }

    // Afisarea continutului unui tabel precizat, existent in baza de date.

    else if (strcmp(ptr, "PRINT") == 0) {
      ptr = strtok(NULL, " ");
      PRINT(DB, ptr);
    }

    // Cautarea intr-un tabel precizat a liniilor al caror continut dintr-o
    // anumita coloana respecta o anumita relatie in raport cu o valoare
    // precizata, cat si afisarea acestora.

    else if (strcmp(ptr, "SEARCH") == 0) {
      char *table_name, *col_name, *rel, *val;

      ptr = strtok(NULL, " ");
      table_name = strdup(ptr);
      if (!table_name) {
        free(cmd);
        free(cmd_cpy);
        if (DB) {
          DELETE_DB(&DB);
        }
        return 1;
      }

      ptr = strtok(NULL, " ");
      col_name = strdup(ptr);
      if (!col_name) {
        free(cmd);
        free(cmd_cpy);
        free(table_name);
        if (DB) {
          DELETE_DB(&DB);
        }
        return 1;
      }

      ptr = strtok(NULL, " ");
      rel = strdup(ptr);
      if (!rel) {
        free(cmd);
        free(cmd_cpy);
        free(table_name);
        free(col_name);
        if (DB) {
          DELETE_DB(&DB);
        }
        return 1;
      }

      ptr = strtok(NULL, " ");
      val = strdup(ptr);
      if (!val) {
        free(cmd);
        free(cmd_cpy);
        free(table_name);
        free(col_name);
        free(rel);
        if (DB) {
          DELETE_DB(&DB);
        }
        return 1;
      }

      SEARCH(DB, table_name, col_name, rel, val);

      free(table_name);
      free(col_name);
      free(rel);
      free(val);
    }

    // Adaugarea unei linii de date intr-un tabel precizat din baza de date
    // existenta.

    else if (strcmp(ptr, "ADD") == 0) {
      char *table_name, *table_data = calloc(MAX_CMD_LEN, sizeof(char));

      if (!table_data) {
        free(cmd);
        free(cmd_cpy);
        if (DB) {
          DELETE_DB(&DB);
        }
        return 1;
      }

      ptr = strtok(NULL, " ");
      table_name = strdup(ptr);
      if (!table_name) {
        free(cmd);
        free(cmd_cpy);
        free(table_data);
        if (DB) {
          DELETE_DB(&DB);
        }
        return 1;
      }

      ptr = strtok(NULL, " ");
      while (ptr != NULL) {
        strcat(table_data, ptr);
        ptr = strtok(NULL, " ");
        if (ptr != NULL) {
          strcat(table_data, " ");
        }
      }

      ADD(DB, table_name, table_data);

      free(table_data);
      free(table_name);
    }

    // Eliminarea continutului unui tabel precizat.

    else if (strcmp(ptr, "CLEAR") == 0) {
      ptr = strtok(NULL, " ");
      CLEAR(DB, ptr);
    }

    // Stergerea bazei de date

    else if (strcmp(ptr, "DELETE_DB") == 0) {
      DELETE_DB(&DB);
      end = 0;
    }

    // Stergerea unui tabel precizat.

    else if (strcmp(ptr, "DELETE") == 0) {
      ptr = strtok(NULL, " ");
      char *aux_ptr = strdup(ptr);
      if (!aux_ptr) {
        free(cmd);
        free(cmd_cpy);
        if (DB) {
          DELETE_DB(&DB);
        }
        return 1;
      }
      ptr = strtok(NULL, " ");
      if (ptr == NULL) {
        DELETE_TABLE(DB, aux_ptr);
        free(aux_ptr);
      }

      // Cautarea intr-un tabel precizat a liniilor al caror continut dintr-o
      // anumita coloana respecta o anumita relatie in raport cu o valoare
      // precizata, cat si eliminarea acestora.

      else {
        char *col_name, *rel, *val;

        col_name = strdup(ptr);
        if (!col_name) {
          free(cmd);
        free(cmd_cpy);
          free(aux_ptr);
          if (DB) {
            DELETE_DB(&DB);
          }
          return 1;
        }

        ptr = strtok(NULL, " ");
        rel = strdup(ptr);
        if (!rel) {
          free(cmd);
        free(cmd_cpy);
          free(aux_ptr);
          free(col_name);
          if (DB) {
            DELETE_DB(&DB);
          }
          return 1;
        }

        ptr = strtok(NULL, " ");
        val = strdup(ptr);
        if (!val) {
          free(cmd);
        free(cmd_cpy);
          free(aux_ptr);
          free(col_name);
          free(rel);
          if (DB) {
            DELETE_DB(&DB);
          }
          return 1;
        }

        DELETE(DB, aux_ptr, col_name, rel, val);

        free(aux_ptr);
        free(col_name);
        free(rel);
        free(val);
      }
    } 

    // Comanda inexistenta.

    else {
      printf("Unknown command: \"%s\".\n", cmd_cpy);
    }

    if (cmd) {
      free(cmd);
    }

    if (cmd_cpy) {
      free(cmd_cpy);
    }
  }
  return 0;
}
