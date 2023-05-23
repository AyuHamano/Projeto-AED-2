import os
import random

articles = ["The ", ""]

adjectives = ["Ugly ", "Beautiful ", "High ", "Forgotten ", "Ocult ", "Solitary ", "Sad ", "Unexpected "]

main_name = ["Castle", "House", "Computer", "Moon", "Love", "Quest", "Star", "Stone", "Life", "Justice", "Game",
                  "Tears", "Legends", "Problems", "Books", "Worlds"]

author_name = ["Bradley ", "Antoinette ", "Cecil ", "Virgil ", "Mary ", "Alice ", "Aline ", "Stephany ", "John ",
               "Ophelia ", "Tristan ", "Vladimir "]

author_surname = ["Rock", "Stockton", "Cooper", "Satchel", "Ferreira", "Kael", "O'Neal", "Giddey", "Sana",
                  "Nart", "Fleta", "Carlton", "Johnson", "Elk"]

total_testcases = 1



# Create the 'testcases' directory if it doesn't exist
if not os.path.exists('testcases'):
    os.makedirs('testcases')

for i in range(1, total_testcases + 1):
    insertions = random.randint(3000, 4000)
    queries = random.randint(2000, insertions)
    deletions = 1000
    filename = f"./testes/input{i}.txt"  # File path with the current testcase number
    array_code = list(range(1, 100000))
    array_used_code = []
    array_used_title = []

    with open(filename, 'w') as file:
        for _ in range(insertions):
            code = random.choice(array_code)
            array_code.remove(code)
            array_used_code.append(code)
            r_article = random.choice(articles)
            r_adjective = random.choice(adjectives)
            r_name = random.choice(main_name)

            array_used_title.append(r_article + r_adjective + r_name)

            a_name = random.choice(author_name)
            a_surname = random.choice(author_surname)

            file.write("1\n")
            file.write(str(code) + '\n')
            file.write(r_article + r_adjective + r_name + '\n')
            file.write(a_name + a_surname + '\n')

        for _ in range(queries): #code queries
            code = random.choice(array_used_code)
            file.write("2\n")
            file.write(str(code) + '\n')


        for _ in range(queries): #title queries
            title = random.choice(array_used_title)
            file.write("3\n")
            file.write(str(title) + '\n')


        for _ in range(deletions):
            code = random.choice(array_used_code)
            array_used_code.remove(code)
            file.write("4\n")
            file.write(str(code) + '\n')
        


        

        