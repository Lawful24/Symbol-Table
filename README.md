<h1>Symbol Table Application</h1>
<p>
    By László Tárkányi
<p>
<h3>Description</h3>
<p>
    This application finds and analyses the declared variables and functions in .c files. It provides statistics regarding the code of the input file It also creates a new .txt file with a list of identifiers that represent the variables and functions.
</p>
<h3>Build</h3>
<ul>
<p>
    This application was created using the Microsoft Compiler and it should be built with that as well.
</p>
    <li>Unzip the contents of the .zip archive into a dedicated folder/directory.</li>
    <li>Open the Microsoft compiler</li>
    <li>Change the directory to the one where the archive was unzipped to.</li>
    <li><code>cd C:/Example/Symbol_Table</code></li>
    <li>Type: <code>nmake symbol_table</code> to build the Part A of the application</li>
    <li>Alternatively, type: <code>nmake symbol_table_b</code> to build the Part B of the application</li>
    <li>Or, you can build both parts at the same time by typing: <code>nmake all</code></li>
    <li>
        Provide arguments to run the program like this:
        <ul>
            <li><code>symbol_table [example.c]</code></li>
            <li><code>symbol_table_b [example.c]</code></li>
        </ul>
    </li>
</ul>

<p>
    I hope it serves your purposes. Enjoy!
</p>