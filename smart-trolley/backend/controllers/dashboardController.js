exports.resetDatabase = async (req, res) => {
    // 1. Clear all cart history and notifications
    await CartItem.destroy({ where: {} });
    await CartSession.destroy({ where: {} });
    await Notification.destroy({ where: {} });
    // 2. Reset stock levels to initial values
    await Product.update(
        { current_count: sequelize.col('initial_count') }, 
        { where: {} }
    );
    // 3. Set all RFID tags to 'AVAILABLE'
    await RFIDTag.update({ status: 'AVAILABLE' }, { where: {} });
    
    res.json({ msg: 'Database reset successfully!' });
};
