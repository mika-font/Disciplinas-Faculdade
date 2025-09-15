public class Comida {
    private int codigo;
    private float preco;
    private int validade;
    private int fabricacao;
    private String setor;
    private float peso;
    private String marca;

    @Override // indica que reimplementa isso daqui
    public String toString() {
        return "Comida [codigo=" + codigo + ", preco=" + preco + ", validade=" + validade + ", fabricacao=" + fabricacao
                + ", setor=" + setor + ", peso=" + peso + ", marca=" + marca + "]";
    }

    public Comida(int codigo, float preco, int validade, int fabricacao, String setor, float peso, String marca) {
        this.codigo = codigo;
        this.preco = preco;
        this.validade = validade;
        this.fabricacao = fabricacao;
        this.setor = setor;
        this.peso = peso;
        this.marca = marca;
    }

    public int getCodigo() {
        return codigo;
    }

    public void setCodigo(int codigo) {
        this.codigo = codigo;
    }

    public float getPreco() {
        return preco;
    }

    public void setPreco(float preco) {
        this.preco = preco;
    }

    public int getValidade() {
        return validade;
    }

    public void setValidade(int validade) {
        this.validade = validade;
    }

    public int getFabricacao() {
        return fabricacao;
    }

    public void setFabricacao(int fabricacao) {
        this.fabricacao = fabricacao;
    }

    public String getSetor() {
        return setor;
    }

    public void setSetor(String setor) {
        this.setor = setor;
    }

    public float getPeso() {
        return peso;
    }

    public void setPeso(float peso) {
        this.peso = peso;
    }

    public String getMarca() {
        return marca;
    }

    public void setMarca(String marca) {
        this.marca = marca;
    }

    public Comida (){
        codigo = 001;
        preco = 100.00f;
        validade = 20240630;
        fabricacao = 20240601;
        setor = "Indefinido";
        peso = 1.0f;
    }

    public class Verdura {

    }

}