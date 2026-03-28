const getWhatsAppLink = () => {
    // 1. Format the item list text
    let itemsText = finalCart.map(item => `- ${item.name}: ₹${item.price * item.quantity}`).join('%0A');
    const date = new Date().toLocaleString();
    
    // 2. Create the receipt content
    const receiptText = `*SMART SHOPPING CART RECEIPT*%0A-----------------------------------------%0A*Date:* ${date}%0A*Status:* PAID%0A*Payment Mode:* ${paymentMode}%0A%0A*Items:*%0A${itemsText}%0A%0A*TOTAL AMOUNT: ₹${finalTotal}*%0A-----------------------------------------%0AThank you for shopping with us!`;
    
    // 3. Return the pre-formatted WhatsApp link
    return `https://wa.me/91${phoneNumber}?text=${receiptText}`;
};
