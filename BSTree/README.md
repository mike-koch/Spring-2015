# BSTree - A Binary Search Tree Implementation
BSTree is a simple "dictionary" application. Below are the supported features.

## Supported Features
This list has been taken directly from the application's "help" screen. `<string>` indicates the string entered / found, and `<nnn>` indicates its count.
 - `insert <string>:` Inserts the string into the tree. If `<string>` already exists, its counter is incremented by 1. `<string>` and its count is then displayed.
 - `delete <string>:` Decrements `<string>`'s counter by 1. If `<string>`'s counter is 0 after decrementing, `<string>` is removed from the tree. If `<string>` is not in the tree, `<string> <-1>` is displayed
 - `search <string>:` Searches for `<string>` in the tree. If `<string>` is in the set, `<string> <nnn>` is displayed, where `<nnn>` is the number of occurrences in the set. Otherwise `<string> <0>` is displayed.
 - `min:` Displays `<string>`, where `<string>` is the smallest value in the set. If the set is empty, there is no output.
 - `max:` Displays `<string>`, where `<string>` is the largest value in the set. If the set is empty, there is no output.
 - `next <string>:` If `<string>` is in the set, the next value in the set is shown. If `<string>` is the max, or is not in the set, there is no output.
 - `prev <string>:` If `<string>` is in the set, the previous value in the set is shown. If `<string>` is the min, or is not in the set, there is no output.
 - `list:` Outputs all items in the set in order from min to max.
 - `help:` Displays the help screen.
 - `exit:` Exits the program.