#include <stdio.h>

#include "cg.h"

FILE *tab(FILE *out) {
    fprintf(out, "\t");
    return out;
}

int find_off(enum TokenType *toks, int *i, enum TokenType what) {
    int off = 1;
    while (toks[*i + 1] == what) {
        off += 1;
        *i += 1;
    }
    return off;
}

void generate(FILE *out, const char *name, struct TokenStream toks) {
    gen_preamble(out, name);
    int label_depth = 0;
    int label_stack[256];
    int label_stack_index = 0;
    for (int i = 0; i < toks.length; i++) {
        switch (toks.toks[i]) {
        case LEFT_IND:
            fprintf(out, ".L%d_begin:\n", label_depth);
            fprintf(out, "\tcmpb\t$0, (%%r14)\n");
            fprintf(out, "\tje  \t.L%d_end\n", label_depth);
            label_stack[label_stack_index++] = label_depth++;
            break;
        case RIGHT_IND:
            fprintf(out, "\tjmp \t.L%d_begin\n", label_stack[label_stack_index - 1]);
            fprintf(out, ".L%d_end:\n", label_stack[--label_stack_index]);
            break;
        case LEFT_ANGLE:
            fprintf(out, "\tsubq\t$%d, %%r14\n",
                find_off(toks.toks, &i, toks.toks[i]));
            break;
        case RIGHT_ANGLE:
            fprintf(out, "\taddq\t$%d, %%r14\n",
                find_off(toks.toks, &i, toks.toks[i]));
            break;
        case INCREMENT:
            fprintf(out, "\taddb\t$%d, (%%r14)\n",
                find_off(toks.toks, &i, toks.toks[i]));
            break;
        case DECREMENT:
            fprintf(out, "\tsubb\t$%d, (%%r14)\n",
                find_off(toks.toks, &i, toks.toks[i]));
            break;
        case READ:
            fprintf(out, "\tcall\tgetchar@PLT\n"
                    "\tmovb\t%%al, (%%r14)\n");
            break;
        case WRITE:
            fprintf(out, "\tmovb\t(%%r14), %%dil\n"
                    "\tcall\tputchar@PLT\n");
            break;
        default: break;
    }

    }
    gen_postamble(out);
}

void gen_preamble(FILE *out, const char *name) {
    fprintf(out,
        "\t.file \"%s\"\n"
        "\t.align 8\n"
        "\t.text\n"
        "\t.globl main\n"
        "\t.type main, @function\n"
        "main:\n"
        "\tpushq\t%%rbp\n"
        "\tmovq\t%%rsp, %%rbp\n"
        "\tsubq\t$16, %%rsp\n"
        "\tmovq\t$30000, %%rdi\n"
        "\tcall\tmalloc@PLT\n"
        "\tmovq\t%%rax, -8(%%rbp)\n\n"
        "\tmovq\t-8(%%rbp), %%rdi\n"
        "\tmovq\t$0, %%rsi\n"
        "\tmovq\t$30000, %%rdx\n"
        "\tcall\tmemset@PLT\n\n"
        "\tmovq\t-8(%%rbp), %%r14\n", name);
}

void gen_postamble(FILE *out) {
    fprintf(out,
        "\tmovq\t-8(%%rbp), %%rdi\n"
        "\tcall\tfree@PLT\n"
        "\tmovq\t%%rbp, %%rsp\n"
        "\tpopq\t%%rbp\n"
        "\tmovq\t$0, %%rax\n"
        "\tret\n"
    );
}
