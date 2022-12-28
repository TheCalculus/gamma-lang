<article class="markdown-body entry-content container-lg" itemprop="text"><p dir="auto"><a target="_blank" rel="noopener noreferrer" href="https://github.com/TheCalculus/gamma/blob/main/assets/the%20gamma%20programming%20language.png?raw=true"><img src="https://github.com/TheCalculus/gamma/raw/main/assets/the%20gamma%20programming%20language.png?raw=true" width="50%" style="max-width: 100%;"></a><br>
A language written in pure C, for pure enjoyment.</p>
<hr>
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
<div class="snippet-clipboard-content notranslate position-relative overflow-auto"><pre class="notranslate"><code>import &lt;stdio&gt;

var x: int = 10;
var addFive: int =&gt; {
    return x + 5;
}

fn main() -&gt; int { // equivalent to var  main: int =&gt;  { ... }
    printf("%d", addFive(x)); // valid
    printf(addFive(x)); // also valid
}
</code></pre><div class="zeroclipboard-container position-absolute right-0 top-0">
    <clipboard-copy aria-label="Copy" class="ClipboardButton btn js-clipboard-copy m-2 p-0 tooltipped-no-delay" data-copy-feedback="Copied!" data-tooltip-direction="w" value="import <stdio>

var x: int = 10;
var addFive: int => {
    return x + 5;
}

fn main() -> int { // equivalent to var  main: int =>  { ... }
    printf(&quot;%d&quot;, addFive(x)); // valid
    printf(addFive(x)); // also valid
}" tabindex="0" role="button">
      <svg aria-hidden="true" height="16" viewBox="0 0 16 16" version="1.1" width="16" data-view-component="true" class="octicon octicon-copy js-clipboard-copy-icon m-2">
    <path fill-rule="evenodd" d="M0 6.75C0 5.784.784 5 1.75 5h1.5a.75.75 0 010 1.5h-1.5a.25.25 0 00-.25.25v7.5c0 .138.112.25.25.25h7.5a.25.25 0 00.25-.25v-1.5a.75.75 0 011.5 0v1.5A1.75 1.75 0 019.25 16h-7.5A1.75 1.75 0 010 14.25v-7.5z"></path><path fill-rule="evenodd" d="M5 1.75C5 .784 5.784 0 6.75 0h7.5C15.216 0 16 .784 16 1.75v7.5A1.75 1.75 0 0114.25 11h-7.5A1.75 1.75 0 015 9.25v-7.5zm1.75-.25a.25.25 0 00-.25.25v7.5c0 .138.112.25.25.25h7.5a.25.25 0 00.25-.25v-7.5a.25.25 0 00-.25-.25h-7.5z"></path>
</svg>
      <svg aria-hidden="true" height="16" viewBox="0 0 16 16" version="1.1" width="16" data-view-component="true" class="octicon octicon-check js-clipboard-check-icon color-fg-success d-none m-2">
    <path fill-rule="evenodd" d="M13.78 4.22a.75.75 0 010 1.06l-7.25 7.25a.75.75 0 01-1.06 0L2.22 9.28a.75.75 0 011.06-1.06L6 10.94l6.72-6.72a.75.75 0 011.06 0z"></path>
</svg>
    </clipboard-copy>
  </div></div>
</article>
