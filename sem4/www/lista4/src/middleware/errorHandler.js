module.exports = (err, req, res, next) => {
	console.error(err);
	const status = err.statusCode || 500;
	const resp = {message: err.message || 'Błąd serwera.'};
	res.status(status).json(resp);
}