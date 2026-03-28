const sendReceiptToAdmin = async (session) => {
    const owner = await User.findOne({ where: { role: 'OWNER' } });
    const mailOptions = {
        from: `"Smart Cart Billing" <${process.env.EMAIL_USER}>`,
        to: owner.email,
        subject: `Sales Report: New Bill Generated (#${session.session_id.substring(0, 8)})`,
        html: `
            <h2>Sales Record</h2>
            <p><b>Session ID:</b> ${session.session_id}</p>
            <p><b>Customer Phone:</b> ${session.phone_number}</p>
            <p><b>Total Amount:</b> ₹${session.total_amount}</p>
            <p>A structured sales report has been added to your database.</p>
        `
    };
    await transporter.sendMail(mailOptions);
};
