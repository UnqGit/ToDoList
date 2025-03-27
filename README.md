# TO DO LIST
It is a very flexible console to do list, you can add, delete, edit, set priority, mark complete/incomplete.
> It uses a txt file, not a *json* file as i haven't learned that yet but it uses a custom delimiter for proper parsing.

## HOW TO RUN
If using an online IDE(for eg, onlineGDB, replit) to test it, make 4 files, named main.cpp todo.h todo.cpp tasks.txt and run it after pasting the contents.
If using a compiler, enter:

`g++ -o output main.cpp todo.cpp`
and run it using:

`./output`

[How to run the program](https://www.youtube.com/watch?v=dQw4w9WgXcQ)

### EXAMPLE
```
What do you want to do:
1. Show tasks.
2. Create task.
3. Delete task.
4. Mark task complete.
5. Mark task incomplete.
6. Set priority.
7. Edit a task.
Enter your choice:
1

🟡TASK: 🔴INCOMPLETE: This is the description for the task named 'TASK'
🟡task: 🟢COMPLETE: This is the description for the task named 'task'
```
> You'll get coloured responses , i just used emojis here for workarounds...

### LICENSE
use it however you'd like idc but if anything goes rogue, `don't put the blame on me, i am only human after all` :D

### FUTURE PLAN
Add json file for more modularity

## THE END
> what you waiting for? `IT'S OVER`
