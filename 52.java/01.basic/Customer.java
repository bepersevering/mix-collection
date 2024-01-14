public interface Customer {
    boolean isVIP();
}

class Merchant {
    public java.lang.Number actionPrice(double price, Customer customer) {
        return null;
    }
}

class NativeMerchant extends Merchant {
    @Override
    public Number actionPrice(double price, Customer customer) {
        // TODO Auto-generated method stub
        return super.actionPrice(price, customer);
    }
}
