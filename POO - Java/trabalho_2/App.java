public class App {
    public static void main(String[] args) {
        Cadeira[] cadeiras = new Cadeira[5];
        cadeiras[0] = new Cadeira("Plástico", 98.99);
        cadeiras[1] = new CadeiraGiratoria("Metal", 354.0, true);
        cadeiras[2] = new Cadeira("Madeira", 150.30);
        cadeiras[3] = new CadeiraGiratoria("Couro", 549.0, false);
        cadeiras[4] = new Cadeira("Fibra", 201.19);

        for (Cadeira cadeira : cadeiras) {
            System.out.println(cadeira.toString());
            System.out.println("Preço Final: R$" + cadeira.getPreco());
            if (cadeira instanceof CadeiraGiratoria) {
                System.out.println("Tipo: Cadeira Giratória");
            } else {
                System.out.println("Tipo: Cadeira Comum");
            }
            System.out.println();
        }
    }
}
