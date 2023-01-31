<article class="markdown-body entry-content container-lg" itemprop="text"><p dir="auto"><a target="_blank" rel="noopener noreferrer" href="https://github.com/TheCalculus/gamma/blob/main/assets/the%20gamma%20programming%20language.png?raw=true"><img src="https://github.com/TheCalculus/gamma-lang/blob/main/the%20gamma%20programming%20language.png?raw=true" width="50%" style="max-width: 100%;"></a><br>
A language written in pure C, for pure enjoyment.</p>
<hr>
Code in main branch @ <a href="https://github.com/TheCalculus/gamma-lang/tree/master">this link</a>
Currently support TOKENS (ARITHMETIC OPERATORS, EXPRESSION, KEYWORDS, MISC) sorted alphabetically.<br>
<table>
    <tbody><tr>
        <td>TOKEN NAME</td>
        <td>PURPOSE</td>
    </tr>
    <tr>
        <td>ARM_DIV</td>
        <td>TOKEN for division operator '/'</td>
    </tr>
    <tr>
        <td>ARM_MOD</td>
        <td>TOKEN for modulo operator '%'</td>
    </tr>
    <tr>
        <td>ARM_MUL</td>
        <td>TOKEN for multiplication operator '*'</td>
    </tr>
    <tr>
        <td>ARM_PLU</td>
        <td>TOKEN for addition operator '+'</td>
    </tr>
    <tr>
        <td>ARM_SUB</td>
        <td>TOKEN for subtraction operator '-'</td>
    </tr>
    <tr>
        <td>EXP_ASG</td>
        <td>EXPRESSION to identify ASSIGNMENT (x = 5)</td>
    </tr>
    <tr>
        <td>EXP_BEG</td>
        <td>EXPRESSION to identify beginning of EXPRESSION '('</td>
    </tr>
    <tr>
        <td>EXP_DEF</td>
        <td>EXPRESSION to identify DEFINITION 'var', 'fn'</td>
    </tr>
    <tr>
        <td>EXP_END</td>
        <td>EXPRESSION to identify end of EXPRESSION ')'</td>
    </tr>
    <tr>
        <td>IDENTIF</td>
        <td>TOKEN for IDENTIFIERS (variable names)</td>
    </tr>
    <tr>
        <td>KWD_FLT</td>
        <td>KEYWORD for FLOATING POINT NUMBERS (1.0f, 2.2f)</td>
    </tr>
    <tr>
        <td>KWD_FUN</td>
        <td>KEYWORD for FUNCTIONS 'fn', 'func'</td>
    </tr>
    <tr>
        <td>KWD_NUL</td>
        <td>KEYWORD for NULL value 'null'</td>
    </tr>
    <tr>
        <td>KWD_RET</td>
        <td>KEYWORD for RETURN 'return'</td>
    </tr>
    <tr>
        <td>TYPE_ANN</td>
        <td>TYPE ANNOTATION, determines type of defined EXPRESSION 'var x: int', where ':' is TYPE_ANN</td>
    </tr>
    <tr>
        <td>THE_EOI</td>
        <td>The END-OF-INSTRUCTION ';'</td>
    </tr>
    <tr>
        <td>THE_EOF</td>
        <td>The END-OF-FILE</td>
    </tr>
</tbody></table><br>
Basic Syntax:
(read test.gamma in branch master for syntax currently being tested / implemented)

```
var x: int = 10;
var addFive: int => {
    return x + 5;
}

fn main() -> int { // equivalent to var  main: int =>  { ... }
    printf(&quot;%d&quot;, addFive(x)); // valid
    printf(addFive(x)); // also valid
}
```
