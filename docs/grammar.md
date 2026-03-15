$$

\text{\_PROG} \to \text{\_STMT\_LIST}  \\
\text{\_STMT\_LIST} \to \text{\_STMT \_STMT\_LIST | } \epsilon \\
\text{\_STMT} \to \text{kill(\_EXPR);} \\
\text{\_STMT} \to \text{let IDENT = \_EXPR;} \\
\text{\_STMT} \to \text{IDENT = \_EXPR} \\
\text{\_STMT} \to \text{print(\_EXPR)}   \\
\text{\_EXPR} \to \text{\_AEXPR} \\ 
\text{\_AEXPR} \to \text{\_TERM \_AEXPR\_R} \\
\text{\_AEXPR\_R} \to \text{ + \_TERM \_AEXPR\_R | - \_TERM \_AEXPR\_R | } \epsilon  \\
\text{\_TERM} \to \text{\_FACTOR \_TERM\_R} \\
\text{\_TERM\_R} \to \text{*\_FACTOR \_TERM\_R | /\_FACTOR \_TERM\_R | } \epsilon \\
\text{\_FACTOR} \to \text{IDENT | INT\_LIT | (\_EXPR)}
$$