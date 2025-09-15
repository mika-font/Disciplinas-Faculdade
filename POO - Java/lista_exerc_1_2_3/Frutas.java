public class Frutas extends Comida {
    private String importado, estacao;

    @Override
    public String toString() {
        return "Frutas [importado=" + importado + ", estacao=" + estacao + "]";
    }

    public Frutas(int codigo, float preco, int validade, int fabricacao, String setor, float peso, String marca,
            String importado, String estacao) {
        super(codigo, preco, validade, fabricacao, setor, peso, marca);
        this.importado = importado;
        this.estacao = estacao;
    }

    public String getImportado() {
        return importado;
    }

    public void setImportado(String importado) {
        this.importado = importado;
    }

    public String getEstacao() {
        return estacao;
    }

    public void setEstacao(String estacao) {
        this.estacao = estacao;
    }

}
