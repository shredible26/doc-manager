/*
  Shrey Varma
  UID: 118019727
  DirectoryID: shreyv
  
  This program immitates a document and contains various methods so that the 
  user can edit the document. Some functionality includes adding paragraphs, 
  lines, removing paragraphs, lines, replacing text, resetting the document,
  and some other editing functions.
  */

#include <stdio.h>
#include <string.h>
#include "document.h"

/* Initializes the document to be empty */
int init_document(Document *doc, const char *name) {
    if (doc == NULL || name == NULL || strlen(name) > MAX_STR_SIZE) {
        return FAILURE;
    }
    strcpy(doc->name, name);
    doc->number_of_paragraphs = 0;
    return SUCCESS;
}

/* Sets number of paragraphs to 0 */
int reset_document(Document *doc) {
    if (doc == NULL) {
        return FAILURE;
    }
    doc->number_of_paragraphs = 0;
    return SUCCESS;
}

/* Prints the documents name, paragraph numbers, and text */
int print_document(Document *doc) {
  int a, b;
  
  if (doc != NULL) {
    printf("Document name: \"%s\"\n", doc->name);
    printf("Number of Paragraphs: %d\n", doc->number_of_paragraphs);
    /* Iterates through the document by paragraph */
    for (a = 0; a < doc->number_of_paragraphs; a++) {
      if (doc->paragraphs[a].number_of_lines > 0) {
        /* Iterates through the document by line in a paragraph*/
        for (b = 0; b < doc->paragraphs[a].number_of_lines; b++) {
          printf("%s\n", doc->paragraphs[a].lines[b]);
        }
        if (a < (doc->number_of_paragraphs - 1)) {
          printf("\n");
	      }
      }
    }
    return SUCCESS;
  }
  return FAILURE;
}

/* Adds a paragraph after a specific paragraph number */
int add_paragraph_after(Document *doc, int paragraph_number) {
  int a, first = 0, last = 0, number_paragraphs = 0;
  
  /* Failing conditions */
  if (doc != NULL) {
    number_paragraphs = doc->number_of_paragraphs;
    if (number_paragraphs < MAX_PARAGRAPHS && paragraph_number 
        <= number_paragraphs) {
      /* Adds paragraph to the beginning of the doc */
      if (paragraph_number == 0 && !number_paragraphs) {
        doc->paragraphs[0].number_of_lines = 0;
      }
      /* Adds paragraph is at the end of the doc */
      if (paragraph_number == doc->number_of_paragraphs) {
        last = doc->number_of_paragraphs;
        doc->paragraphs[last].number_of_lines = 0;
      /* If paragraph is in the middle of the doc */
      } else {
        first = doc->number_of_paragraphs;
        for (a = first; a >= paragraph_number; a--) {
          doc->paragraphs[a + 1] = doc->paragraphs[a];
        }
        doc->paragraphs[paragraph_number].number_of_lines = 0;
      }
      (doc->number_of_paragraphs)++;
      return SUCCESS;
    }
  }
  return FAILURE;
}

/* Adds a new line after specified line number */
int add_line_after(Document *doc, int paragraph_number, int line_number, 
                  const char *new_line) {
  int b, num_of_lines = 0;
  char *pos, *first, *second;

  /* Failing conditions */
  if (doc != NULL && new_line != NULL && paragraph_number 
        <= doc->number_of_paragraphs) {
      num_of_lines = doc->paragraphs[paragraph_number - 1].number_of_lines;
      if (num_of_lines < MAX_PARAGRAPH_LINES && line_number <= num_of_lines) {
        /* If line is at the beginning of the paragraph */
        if (line_number == 0 && !num_of_lines) {
          pos = doc->paragraphs[paragraph_number - 1].lines[0];
          strcpy(pos, new_line);
        /* If line is at the end of the paragraph */
        } else if (line_number == num_of_lines) {
          pos = doc->paragraphs[paragraph_number - 1].lines[line_number];
          strcpy(pos, new_line);
        /* If line is in the middle of the paragraph */
        } else {
          /* Manipulates the lines to insert, like a linked list */
          for (b = num_of_lines; b >= line_number; b--) {
	          second = doc->paragraphs[paragraph_number - 1].lines[b + 1];
            first = doc->paragraphs[paragraph_number - 1].lines[b];
            strcpy(second, first);
          }
          pos = doc->paragraphs[paragraph_number - 1].lines[line_number];
          strcpy(pos, new_line);
        }
        /* Accounts for added line */
        (doc->paragraphs[paragraph_number - 1].number_of_lines)++;
        return SUCCESS;
      }
    
  }
  return FAILURE;
}

/* Gets the number of lines in a paragraph */
int get_number_lines_paragraph(Document *doc, int paragraph_number, 
                              int *number_of_lines) {
/* Failing conditions */
if (doc != NULL || number_of_lines == NULL || 
  paragraph_number > doc->number_of_paragraphs) {
  return FAILURE;
}
  *number_of_lines = doc->paragraphs[paragraph_number - 1].number_of_lines;
  return SUCCESS;
}

/* Gets the total number of lines in the document */
int get_number_lines(Document *doc, int *number_of_lines) {
  int x, count = 0;

  if (doc == NULL || number_of_lines == NULL) {
    return FAILURE;
  }
  /* Iterated through each paragraph and adds up lines */
  for (x = 0; x < doc->number_of_paragraphs; x++) {
    count += doc->paragraphs[x].number_of_lines;
  }
  *number_of_lines = count;
  return SUCCESS;
}

/* Appends a line to a specific paragraph */
int append_line(Document *doc, int paragraph_number, const char *new_line) {
  int num_of_lines = 0;

  /* Failing conditions */
  if (doc != NULL && new_line != NULL) {
    num_of_lines = doc->paragraphs[paragraph_number - 1].number_of_lines;
    if (paragraph_number <= MAX_PARAGRAPHS && 
        num_of_lines < MAX_PARAGRAPH_LINES) {
      /* Calls previous method to add line */
      add_line_after(doc, paragraph_number, num_of_lines, new_line);
      return SUCCESS;
    }
  }
  return FAILURE;
}

/* Removes a line from a specified paragraph */
int remove_line(Document *doc, int paragraph_number, int line_number) {
  int a, b, num_of_lines = 0;
  char *first, *second;

  if (doc != NULL) {
    num_of_lines = doc->paragraphs[paragraph_number - 1].number_of_lines;
    if (paragraph_number <= doc->number_of_paragraphs 
          && line_number <= num_of_lines) {
        /* Iterates thorugh paragraph and shifts each line by one to remove */
        for (a = line_number - 1; a < num_of_lines - 1; a++) {
	        second = doc->paragraphs[paragraph_number - 1].lines[a + 1];
            first = doc->paragraphs[paragraph_number - 1].lines[a];
            for (b = 0; b < MAX_STR_SIZE; b++) {
                first[b] = second[b];
            }
        }
        /* Subtracts number of lines by one to account for removal */
        (doc->paragraphs[paragraph_number - 1].number_of_lines)--;
        return SUCCESS;
    }
  }
  return FAILURE;
}

/* Adds data from the data array to the document */
int load_document(Document *doc, char data[][MAX_STR_SIZE + 1], 
  int data_lines) {
  int a = 0;
  /* Failing conditions */
  if (doc != NULL && data != NULL && data_lines > 0) {
    add_paragraph_after(doc, doc->number_of_paragraphs);
    for (a = 0; a < data_lines; a++) {
      if (strcmp(data[a], "") == 0) {
        add_paragraph_after(doc, doc->number_of_paragraphs);
      } else {
        append_line(doc, doc->number_of_paragraphs, data[a]);
      }
    }
    return SUCCESS;
  }
  return FAILURE;
}

/* Replaces target text with replacement parameter */
int replace_text(Document *doc, const char *target, const char *replacement) {
  int a, b, num_of_lines = 0;
  char *pos, temp[MAX_STR_SIZE + 1] = {0};

  if (doc == NULL && target == NULL && replacement == NULL) {
    return FAILURE;
  }
    /* Iterates through each paragraph */
    for (a = 0; a < doc->number_of_paragraphs; a++) {
    num_of_lines = doc->paragraphs[a].number_of_lines;
    /* Iterates through each line */
    for (b = 0; b < num_of_lines; b++) {
        pos = strstr(doc->paragraphs[a].lines[b], target);
        /* Continues until reaching the end of the line */
        while (pos != '\0') {
          strcpy(temp, pos);
          strcpy(pos, "");
          strcat(pos, replacement);
          strcat(pos + strlen(replacement), temp + strlen(target));
          pos = strstr(pos + strlen(target), target);
        }
      }
    }
    return SUCCESS;
}

/* Highlights the text associated with target parameter */
int highlight_text(Document *doc, const char *target) {
    char result[MAX_STR_SIZE + 1] = "";
    /* Failing conditions */
    if (doc == NULL && target == NULL) {
    return FAILURE;
    }
    strcat(result, HIGHLIGHT_START_STR);
    strcat(result, target);
    strcat(result, HIGHLIGHT_END_STR);
    replace_text(doc, target, result);
    return SUCCESS;  
}

/* Removes target text from the document */
int remove_text(Document *doc, const char *target) {
/* Failing conditions */
if (doc != NULL && target != NULL) {
    replace_text(doc, target, "");
    return SUCCESS;
  }
  return FAILURE;
}
