public class Carne extends Comida {
    private String corte;
    private String raca;
    private String animal;
    private String origem;

    public Carne(int codigo, float preco, int validade, int fabricacao, String setor, float peso, String marca,
            String corte, String raca, String animal, String origem) {
        super(codigo, preco, validade, fabricacao, setor, peso, marca);
        this.corte = corte;
        this.raca = raca;
        this.animal = animal;
        this.origem = origem;
    }
    
    @Override
    public String toString() {
        return "Carne [corte=" + corte + ", raca=" + raca + ", animal=" + animal + ", origem=" + origem + "]";
    }
    public String getCorte() {
        return corte;
    }
    public void setCorte(String corte) {
        this.corte = corte;
    }
    public String getRaca() {
        return raca;
    }
    public void setRaca(String raca) {
        this.raca = raca;
    }
    public String getAnimal() {
        return animal;
    }
    public void setAnimal(String animal) {
        this.animal = animal;
    }
    public String getOrigem() {
        return origem;
    }
    public void setOrigem(String origem) {
        this.origem = origem;
    }

}