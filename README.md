# Ecosystem :tiger2: :mouse2: :herb:
#### This project is a simulation of a predator-prey-plants relationship done in c.
##### Functions are commented on in /include/ecosys.h

## Description 
A predator-prey ecosystem is a community where the predators, hunt, kill, and consume another group of known as prey. The predators rely on the prey for their survival and play an essential role in controlling the prey population. At the same time, the prey is critical to the predator's food source. The interaction between predators and prey is dynamic, with each species adapting to the other over time, resulting in a complex, balanced ecosystem.

## Instalation 
Download the files and unpack them.
Make sure you've installed makefile on your machine :)\
To test functions independently, you can add your tests in /tests/main_tests.c or /tests/main_tests2.c:\
`make` \
`./bin/tests_ecosys`
or
`./bin/tests_ecosys2`

To see the simulation:\
you need to supply two arguments: number of maximum iterations & starting number for prey & predators\
`make`\
`./bin/ecosys 100 50`

Every iteration is printed out in a console:

- * - at least one prey
- O - at least one predator
- @ - at least one prey & one predator

## Credits
This project was done for 'advanced C programming' I took in the third semester of my bachelor's degree in computer science


