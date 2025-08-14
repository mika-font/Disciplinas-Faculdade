public class Retangulo {
    private double largura;
    private double altura;

    public Retangulo(double largura, double altura){
        System.out.println("Criando um retângulo de " + largura + " de largura e " + altura + " de altura.");
        this.largura = largura;
        this.altura = altura;
    }
    public double calcularArea(){ return largura * altura;}
    public double calcularPerimetro(){ return (2*altura) + (2*largura);}

    public double getLargura(){ return this.largura;}
    public double getAltura(){ return this.altura;}

    public static void main(String[] args){
        Retangulo retangulo1 = new Retangulo(2.2, 3);
        Retangulo retangulo2 = new Retangulo(3.8, 1.8);

        System.out.println("--Informações sobre o primeiro Retângulo: --");
        System.out.println("Altura: " + retangulo1.getAltura());
        System.out.println("Largura: " + retangulo1.getLargura());

        double ret1area = retangulo1.calcularArea();
        double ret1peri = retangulo1.calcularPerimetro();

        System.out.println("Área do Retângulo 1: " + ret1area);
        System.out.println("Perímetro do Retângulo 1: " + ret1peri);

        System.out.println("--Informações sobre o segundo Retângulo: --");
        System.out.println("Altura: " + retangulo2.getAltura());
        System.out.println("Largura: " + retangulo2.getLargura());

        double ret2area = retangulo2.calcularArea();
        double ret2peri = retangulo2.calcularPerimetro();

        System.out.println("Área do Retângulo 2: " + ret2area);
        System.out.println("Perímetro do Retângulo 2: " + ret2peri);

    }
}
