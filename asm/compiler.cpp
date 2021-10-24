#include <assert.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "parse.h"
#include "compiler.h"
#include "../include/thrw.h"

/*
static inline int islabel(const token_t *const tok)
{
        return tok->start[tok->len - 1] == ':';
}
*/
/*
static void uncomment(token_t *tok)
{
        char *ch = *tok;
        size_t len = tok->len;
        while (len-- > 0) {
                if (*ch == ';') {
                        //tok->len = (size_t)(ch - tok->start);
                        *ch = '\0';
                        return;
                }
                ch++;
        }
}
*/

int compile_asm(code_t *asm_code, char *const bytecode) 
{
        assert(asm_code);
        static token_t toks[4] = {0};

        //char *end = nullptr;
        size_t n_toks = 0;
        for (size_t c = 0; c < asm_code->n_cmds; c++) {
                //uncomment(&asm_code->cmds[c]);
                n_toks = extract_tokens(asm_code->cmds[c], toks, " \t,", 4);

                for (size_t t = 0; t < n_toks; t++) {
                //       double val = atof(toks[t].start);
                }
        }

        return 0;
}

int decompile_asm(char *bytecode);

int construct_asm_code(code_t *const asm_code, char *const buf)
{
        assert(asm_code);
        assert(buf);

        errno = 0;

        size_t n_toks = 0;
        size_t n_cmds = occurs('\n', buf);

        token_t  *cmds = (token_t *)calloc(n_cmds, sizeof(token_t));
        thrw(finally, (cmds == nullptr),
             "Can't calloc memory for commands: %s", strerror(errno));

        n_toks = extract_tokens(buf, cmds, "\n", n_cmds);
        if (n_toks < n_cmds) {
                n_cmds = n_toks;
                void *mem = realloc(cmds, sizeof(token_t) * n_cmds);
                thrw(finally, (mem == nullptr),
                     "Can't realloc memory for commands: %s", 
                                                     strerror(errno));

                cmds = (token_t *)mem;
        }

        asm_code->  cmds =   cmds;
        asm_code->n_cmds = n_cmds;

finally:
        if (errno)
                free(cmds);

        return errno;
}

void destruct_asm_code(code_t *const asm_code) 
{
        free(asm_code->cmds);
        asm_code->n_cmds = 0;
}
