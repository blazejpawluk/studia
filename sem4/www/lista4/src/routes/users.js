const express = require('express');
const router = express.Router();
const user = require('../controllers/user');
const {verifyToken} = require('../middleware/auth');

router.use(verifyToken);

router.get('/', user.getAllUsers);
router.get('/:id', user.getUserById);
router.put('/:id', user.editUser);
router.delete('/:id', user.removeUser);

module.exports = router;