public class Cadeira {
    private String material;
    private double preco;

    public Cadeira(){
        material = "Madeira";
        preco = 0.0;
    }

    public Cadeira(String material, double preco) {
        this.material = material;
        this.preco = preco;
    }

    public String getMaterial(){
        return material;
    }

    public double getPreco(){
        return preco;
    }

    public void setMaterial(String m){
        material = m;
    }

    public void setPreco(double p){
        preco = p;
    }

    @Override
    public String toString() {
        return "Cadeira de " + material + ", preço R$" + preco;
    }
}
