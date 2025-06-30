require('dotenv').config();
const mongoose = require('mongoose');
const app = require('./app');

mongoose.connect(process.env.MONGODB_URI, {
	useNewUrlParser: true,
	useUnifiedTopology: true,
})
.then(() => console.log('Połączono z bazą'))
.catch(err => {
	console.error('Błąd połączenia z bazą:', err);
	process.exit(1);
});

const port = process.env.PORT || 3000;
app.listen(port, () => {
	console.log(`Serwer startuje na porcie ${port}`);
});