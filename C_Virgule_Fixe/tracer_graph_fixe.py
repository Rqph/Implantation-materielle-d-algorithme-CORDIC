import matplotlib.pyplot as plt

def gen_graphP2():
    values = []
    cos_max = []
    sin_max = []
    n = []
    N = [4,8,16]
    for i in N :
        file = open(f"./data/angle{i}.txt","r")
        values = file.readlines()
        x = []
        y = []
        for j in range(1,len(values)) :
            x.append(float(values[j].split(" | ")[0]))
            y.append(float(values[j].split(" | ")[1]))
        
        plt.figure()
        plt.plot(x,'r*-')
        plt.suptitle(f'Erreur Cos pour n={i} itérations [CODAGE FIXE]')
        plt.title("Phi allant de 0 à 90°")
        plt.yscale('log')
        plt.savefig(f"./graphs/Erreur_cos_{i}_ite.jpg")
        plt.close()
        
        plt.figure()
        plt.plot(y,'g*-')
        plt.suptitle(f'Erreur Sin pour n={i} itérations [CODAGE FIXE]')
        plt.title("Phi allant de 0 à 90°")
        plt.yscale('log')
        plt.savefig(f"./graphs/Erreur_sin_{i}_ite.jpg")
        plt.close()

    for i in range(1,max(N)) :
        n.append(i)
        file = open(f"./data/angle{i}.txt","r")
        values = file.readlines()
        x = []
        y = []
        for j in range(1,len(values)) :
            x.append(float(values[j].split(" | ")[0]))
            y.append(float(values[j].split(" | ")[1]))

        cos_max.append(max(x))
        #print(f"ite : {i} : cos_e_max = {max(x)}")
        sin_max.append(max(y))
        #print(f"ite : {i} : sin_e_max = {max(y)}")
        
        file.close()

    plt.figure()
    plt.plot(n,cos_max,'r*-')
    plt.title(f'Echelle Log')
    plt.suptitle(f'Erreur Cos en fonction de n [CODAGE FIXE]')
    plt.yscale('log')
    plt.savefig("./graphs/Erreur_cos_n_log.jpg")
    plt.close()

    plt.figure()
    plt.plot(n,sin_max,'g*-')
    plt.title(f'Echelle Log')
    plt.suptitle(f'Erreur Sin en fonction de n [CODAGE FIXE]')
    plt.yscale('log')
    plt.savefig("./graphs/Erreur_sin_n_log.jpg")
    plt.close()

    plt.figure()
    plt.plot(n,cos_max,'r*-')
    plt.title(f'Echelle linéaire')
    plt.suptitle(f'Erreur Cos en fonction de n [CODAGE FIXE]')
    plt.savefig("./graphs/Erreur_cos_n_lin.jpg")
    plt.close()

    plt.figure()
    plt.plot(n,sin_max,'g*-')
    plt.title(f'Echelle linéaire')
    plt.suptitle(f'Erreur Sin en fonction de n [CODAGE FIXE]')
    plt.savefig("./graphs/Erreur_sin_n_lin.jpg")
    plt.close()

gen_graphP2()