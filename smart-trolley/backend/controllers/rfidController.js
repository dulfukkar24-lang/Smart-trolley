exports.readRFID = async (req, res) => {
    const { rfid_code } = req.body;
    try {
        const tag = await RFIDTag.findOne({ where: { rfid_code }, include: [Product] });
        if (tag) {
            // Broadcast to all connected clients via Socket.io
            req.io.emit('rfidRead', { 
                name: tag.Product.name, 
                price: tag.Product.price,
                rfid_code: rfid_code
            });
            res.json({ msg: 'Tag read successfully' });
        }
    } catch (err) {
        res.status(500).json({ msg: 'Server error' });
    }
};
