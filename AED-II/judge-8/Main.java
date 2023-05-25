public class Main {
    public static void main(String[] args) {
        Arvore arvore = new Arvore();
        arvore.adiciona(6);
        arvore.adiciona(4);
        arvore.adiciona(5);
        arvore.adiciona(3);
        arvore.adiciona(2);
        arvore.adiciona(7);
        arvore.adiciona(1);
        arvore.print();
    }
}

class Nodo {
    // Uma árvore é composta de vários Nodos (ou nós) ligados entre si e cada um deles conterá:

    public Integer v; // Um valor inteiro, que será a chave para busca, inserção, remoção...
    public Nodo p, esq, dir; // Um Nodo que representa o pai do Nodo em questão,
    // o Nodo que se encontra à esquerda e o que se encontra à direita do mesmo
    public boolean ver; // Uma flag booleana, que quando tiver valor "true",
    // significará que o Nodo em questão é de cor vermelha, caso contrário é preto


    public Nodo(int n, boolean ver) {
        this.v = n;
        this.ver = ver;
        this.p = this.esq = this.dir = Arvore.nil;
    }

    public Nodo encontra(int n) {
        if (n < this.v && this.esq != Arvore.nil) return this.esq.encontra(n);
        else if (n > this.v && this.dir != Arvore.nil) return this.dir.encontra(n);
        else return this;
    }

    public Nodo minimo() {
        // Vai mostrar o valor mais baixo presente na árvore a partir do Nodo que está rodando no momento
        if (this.esq != Arvore.nil) return esq.minimo();
        else return this;
    }

    public Nodo maximo() {
        // Vai mostrar o valor mais alto presente na árvore a partir do Nodo que está rodando no momento
        if (this.dir != Arvore.nil) return dir.maximo();
        else return this;
    }

    public Nodo predecessor() {
        // Informa o valor do Nodo que antecede (em termos de valores)
        // o atual Nodo
        if (this.esq != Arvore.nil) return this.esq.maximo();
        else return this;
    }

    public Nodo sucessor(){
        // Informa o valor do Nodo que sucede (em termos de valores)
        // o atual Nodo
        if (this.dir != Arvore.nil) return this.dir.minimo();
        else return this;
    }
}

class Arvore {
    public Nodo raiz; // Uma árvore sempre terá um Nodo raiz, que fica no nível mais alto da árvore
    // e é este Nodo que é dado por "inicial" na árvore
    public static Nodo nil = new Nodo(0, false); // Nodo sentinela. Todos os nodos no último nível da árvore apontarão para a sentinela
    // que é sempre de cor preta com valor 0
    public Integer cont;

    public Arvore() {
        this.raiz = Arvore.nil;
    }

    public Arvore(int v) {
        this.raiz = new Nodo(v, false);
    }

    // As rotações (rotacao_esq e rotacao_dir) servem para manter o balanceamento da árvore,
// especialmente porque a árvore preta e vermelha tem como característica o balanceamento
    private void rotacao_esq(Nodo x) {
        Nodo y = x.dir;
        x.dir = y.esq;
        if (y.esq != Arvore.nil) y.esq.p = x;
        y.p = x.p;
        if (x.p == Arvore.nil) this.raiz = y;
        else if (x == x.p.esq) x.p.esq = y;
        else x.p.dir = y;
        y.esq = x;
        x.p = y;
    }
    // Ambas as rotações são idênticas, sendo trocados apenas os "dir" e "esq", referentes a direita e esquerda
    private void rotacao_dir(Nodo x) {
        Nodo y = x.esq;
        x.esq = y.dir;
        if (y.dir != Arvore.nil) y.dir.p = x;
        y.p = x.p;
        if (x.p == Arvore.nil) this.raiz = y;
        else if (x == x.p.esq) x.p.esq = y;
        else x.p.dir = y;
        y.dir = x;
        x.p = y;
    }

    public void adiciona (int n) {
        // Método que adiciona um novo nodo com valor n (passado como parâmetro)
        // na árvore que está rodando
        if (this.raiz == Arvore.nil) {
            // Se a árvore ainda estiver vazia, cria o nodo preto e o torna raiz
            this.raiz = new Nodo (n, false);
        } else {
            // Se a árvore já conter um ou mais nodos, faremos uma busca (com o método encontra())
            // para locaizar o local em que o nodo deverá ser adicionado (isso depende do valor do nodo)
            // pois os nodos com valores mais altos ficarão à direita da árvore e os com valores mais baixos à esquerda,
            // ficando, então, ordenados
            Nodo a = this.encontra(n);
            if (n < a.v) {
                // Caso o valor do novo nodo seja menor do que o nodo encontrado, será adicionado à esquerda do mesmo
                a.esq = new Nodo(n, true);
                a.esq.p = a;
                this.fixaadicao(a.esq);
                // Ao final, deve ser chamado o método fixaadicao, que irá corrigir os possíveis casos
                // de desbalanceamento que podem ocorrer
            }	else if (n > a.v) {
                // Caso o valor do novo nodo seja maior do que o nodo encontrado, será adicionado à direita do mesmo
                a.dir = new Nodo(n, true);
                a.dir.p = a;
                this.fixaadicao(a.dir);
                // Ao final, deve ser chamado o método fixaadicao, que irá corrigir os possíveis casos
                // de desbalanceamento que podem ocorrer
            }
        }
    }

    public void transplant (Nodo x, Nodo y) {
        // Realiza troca entre os nós, sendo necessária ao se remover um nodo para evitar perda de ponteiros
        if (x.p == Arvore.nil) this.raiz = y;
        else if (x == x.p.esq) x.p.esq = y;
        else x.p.dir = y;
        y.p = x.p;
    }

    private void fixaadicao(Nodo z) {
        Nodo y;
        while (z.p.ver) {
            if (z.p == z.p.p.esq) {
                y = z.p.p.dir;
                if (y.ver) { // caso 1 (tio é vermelho):
                    // muda a cor do pai e do tio para preto e dos avós para vermelho.
                    // Então, sobe dois níveis na árvore.
                    z.p.ver = false;
                    y.ver = false;
                    z.p.p.ver = true;
                    z = z.p.p;
                }	else { // Ou seja, tio é preto
                    if (z == z.p.dir) { // caso 2
                        z = z.p;
                        this.rotacao_esq(z);
                    }
                    // caso 3
                    z.p.ver = false;
                    z.p.p.ver = true;
                    this.rotacao_dir(z.p.p);
                }
            }	else {
                y = z.p.p.esq;
                if (y.ver) { // caso 1
                    y.ver = z.p.ver = false;
                    z.p.p.ver = true;
                    z = z.p.p;
                }	else {
                    if (z == z.p.esq) { // caso 2
                        z = z.p;
                        this.rotacao_dir(z);
                    }
                    // caso 3
                    z.p.ver = false;
                    z.p.p.ver = true;
                    this.rotacao_esq(z.p.p);
                }
            }
        }
        this.raiz.ver = false;
    }

    public Nodo minimo() {
        return this.raiz.minimo();
    }

    public Nodo maximo() {
        return this.raiz.maximo();
    }

    public Nodo encontra (int n) {
        return this.raiz.encontra(n);
    }

    private void print(Nodo nodo) {
        if (nodo != null && nodo != nil) {
            System.out.print(nodo.v + "(" + nodo.ver + ") ");
            print(nodo.esq);
            print(nodo.dir);
        }
    }

    public void print() {
        print(raiz);
    }
}