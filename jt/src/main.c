/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
 * File Name   : main.c
 * Created at  : 2024-03-17
 * Updated at  : 2024-03-18
 * Author      : jeefo
 * Purpose     :
 * Description :
.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.*/
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <tree_sitter/api.h>
#include <tree_sitter/parser.h>

char* readfile(const char *filename) {
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    perror("Error opening file");
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  fseek(file, 0, SEEK_SET);

  // Allocate memory to store the entire file
  char* buffer = (char*)malloc(file_size + 1);
  if (buffer == NULL) {
    fclose(file);
    perror("Buy some RAM!");
    return NULL;
  }

  size_t bytes_read  = fread(buffer, 1, file_size, file);
  buffer[bytes_read] = 0;
  fclose(file);

  return buffer;
}

extern TSLanguage* tree_sitter_jeefo_template(void);

int main(int argv, char** argc) {
  if (argv < 2) {
    perror("Argument filename is required.\n");
    return 1;
  }

  // Create a parser.
  TSParser*   parser         = ts_parser_new();
  TSLanguage* jeefo_template = tree_sitter_jeefo_template();

  // Set the parser's language jeefo_template
  assert(ts_parser_set_language(parser, jeefo_template));

  const char* filepath = argc[1];
  char* source_code = readfile(filepath);
  TSTree* tree = ts_parser_parse_string(
    parser,
    NULL,
    source_code,
    strlen(source_code)
  );
  assert(tree != NULL);

  // Get the root node of the syntax tree.
  TSNode root_node = ts_tree_root_node(tree);

  // Print the syntax tree as an S-expression.
  char* string = ts_node_string(root_node);
  printf("Syntax tree: %s\n", string);

  // Free all of the heap-allocated memory.
  free(string);
  free(source_code);
  ts_tree_delete(tree);
  ts_parser_delete(parser);
  return 0;
}