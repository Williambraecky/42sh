# 42sh
Posix shell implementation with limited libraries for the 42network cursus.

# Features

- **Ability to customize the prompt.**
- Complete prompt with edition and multiple line support.
- Redirection and aggregation operators.
- Pipes and separators.
- && and || logical operators.
- Monitoring of intern shell variables.
- Job control monitoring, with buitl-ins jobs, fg, bg and the & operator
- A correct monitoring of all signals
- Inhibitors ” (double quote), ’ (simple quote) and \
- Control substitution: $()
- ZSH-like command completion with scrolling.
- Contextual dynamic completion of commands, built-ins, files, internal and environment variables. What is meant by contextual? re-we use the “ls /” command
and your cursor is on the /, then a contextual completion will only propose the
content of the root folder and not the commands or built-ins. Same for this case:
“echo ${S”, the completion should only propose variable names that start with S,
whether internal or environmental.
- Alias management via built-ins alias and unalias.
- A hash table and built-in hash to interact with it.
- The built-in test with the following operators: texttt-b, -c, -d, -e, -f, -g, -L,
-p, -r, -S, -s, -u, -w, -x, -z, =, !=, -eq, -ne, -ge, -lt, -le, !. As well as the
possibility of a simple operand, without operator.
- Complete management of the history:
  - Expansions:
  - !!
  - !word
  - !number
  - !-number
  - Saving to a file so that it can be used over several sessions
  - Built-in fc (all POSIX options)
  - Incremental search in the history with CTRL-R
- Tilde expansion and additional parameter formats:
  - ~
  - ${parameter:-word}
  - ${parameter:=word}
  - ${parameter:?word}
  - ${parameter:+word}
  - ${#parameter}
  - ${parameter%}
  - ${parameter%%}
  - ${parameter#}
  - ${parameter##}
- The following builtins:
  - cd
  - fc
  - jobs
  - fg
  - bg
  - test
  - alias
  - unalias
  - echo
  - exit
  - export
  - false
  - true
  - hash
  - history
  - pwd
  - rehash
  - set
  - type
  - unset
  - unsetenv
