public class CadeiraGiratoria extends Cadeira {
    private boolean temRodinhas;

    public CadeiraGiratoria(String material, double preco, boolean temRodinhas) {
        super(material, preco);
        this.temRodinhas = temRodinhas;
    }

    @Override
    public String toString() {
        String rodas = temRodinhas ? "com rodas" : "sem rodas";
        return "Cadeira Giratória de " + getMaterial() + ", preço R$" + getPreco() + ", " + rodas;
    }

    @Override
    public double getPreco(){
        double precoBase = super.getPreco();
        double precoFinal = precoBase + (precoBase * 10/100);
        if (temRodinhas) {
            precoFinal += 50.0;
        }
        return precoFinal;
    }
}
