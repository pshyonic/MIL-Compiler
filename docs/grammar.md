$$

\text{\_PROG} \to \text{\_STMT\_LIST}  \\
\text{\_STMT\_LIST} \to \text{\_STMT \_STMT\_LIST | } \epsilon \\
\text{\_STMT} \to \text{kill(\_EXPR);} \\
\text{\_STMT} \to \text{let IDENT = \_EXPR;} \\
\text{\_EXPR} \to \text{IDEN} \\
\text{\_EXPR} \to \text{INT\_LIT}
$$