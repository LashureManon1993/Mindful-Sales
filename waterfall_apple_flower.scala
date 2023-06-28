import scala.collection.mutable

// define product class
class Product(val name: String, val price: Double)

// define customer class
class Customer(val name: String, val credit: Double)

// define shopping cart class with map to store products
class ShoppingCart() {
  val products = mutable.Map[Product, Int]()

  // method to add product to cart
  def addProduct(product: Product, quantity: Int): Unit = {
    products += (product -> quantity)
  }

  // method to calculate total cost
  def calculateTotal(): Double = products.map { case (k, v) => k.price * v }.sum
}

// define discount rule class
class DiscountRule(val customer: Customer, val product: Product, val discountPercentage: Double)

// define store class
class Store(val name: String, val discountRules: Seq[DiscountRule]) {
  val customers = mutable.Map[String, Customer]()
  val products = mutable.Map[String, Product]()

  // method to add a customer
  def addCustomer(customer: Customer): Unit = {
    customers += (customer.name -> customer)
  }

  // method to add a product
  def addProduct(product: Product): Unit = {
    products += (product.name -> product)
  }

  // method to get a customer
  def getCustomer(name: String): Option[Customer] = customers.get(name)

  // method to get a product
  def getProduct(name: String): Option[Product] = products.get(name)

  // method to get discount applied
  def getDiscount(customer: Customer, product: Product): Double =
    discountRules.filter(r => r.customer == customer && r.product == product).map(_.discountPercentage).sum
}

// define mindful sales service class
class MindfulSalesService(val store: Store) {
  // method to generate quote
  def generateQuote(name: String, productName: String, quantity: Int): Option[Double] = {
    // get customer
    val maybeCustomer = store.getCustomer(name)

    maybeCustomer match {
      case None => None
      case Some(customer) =>
        // get product
        val maybeProduct = store.getProduct(productName)

        maybeProduct match {
          case None => None
          case Some(product) =>
            // create a shopping cart
            val cart = new ShoppingCart()
            cart.addProduct(product, quantity)

            // get discount
            val discount = store.getDiscount(customer, product)

            // calculate total cost
            val total = cart.calculateTotal() * (1 - discount)

            // Check if customer has enough credit
            if (customer.credit >= total) Some(total) else None
        }
    }
  }
}