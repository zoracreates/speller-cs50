# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

In the context of this program, it is an example of a word that contains the max amount of characters to be considered a dictionary word.

## According to its man page, what does `getrusage` do?

Returns resource usage measures for either the current process (`RUSAGE_SELF`), child processes of the current process that have terminated (`RUSAGE_CHILDREN`), or for the calling thread (`RUSAGE_THREAD`).

## Per that same man page, how many members are in a variable of type `struct rusage`?

It specifies where the statistics returned by `getrusage` are stored.

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

Because `calculate` needs access to specific fields inside `before` and `after` (`ru_utime.tv_sec`, `ru_utime.tv_usec`, `ru_stime.tv_sec`, `ru_stime.tv_usec`). Therefore what it needs to know is where `before` and `after` are located so that it can the access these values.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

The `for` loop in main goes from character to character inside the text file, until it reaches the charcter that indicated the end of file.
First it verifies that the character is alphabetical or an apostrophee. Any character that is an alphabetical character, or apostrophee gets added to an array called "word".
By remembering the "index" of the current chacter in word, it not only knows where to store the next character, but it also knows the length of the word.
If `index` is larger than `LENGTH` which is the maximum lenght a dictionary word can have, then the current `word` would not be a dictionary word.
Therefore, we set `index` to 0. By setting `index` to 0, we prepare to have new characters  ovewrite the current chacters in `word`; i.e. to start a new word.

In the event the character encountered is not alphabetical or an apostorphee, we check if it is a number. If it is a number, then it will not be in dictionary, which means we must start a new word.

When the current character is not a letter, apostorphee, or number, then the loop determines that this must be the end of a word, and we end the array `word` with a `NULL` terminator.
Then we  use `check` to verify if `word` is infact in the dictionary. If it is not, then it is printed as a mispelling, and we prepare to start a new word. If the word is in the dictionary, the it is not printed and we simply prepare to start a new word.


## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

We do not know that every string on the text file is a word. If we used `fscanf` we would still have to iterate over each character of the current string to verify if it is a letter or an apostorphee, and to calculate its legnth to determine if it could be a word in the dictionary.
Therefore `fscanf` would require adding yet another `for` loop, which may slowdown the prorgram.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

Because we do not intend to change the contents of `word` or `dictionary` as we are running the functions `check` and `load`respectively.
