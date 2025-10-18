import React, {useState, useContext} from 'react';
import {AuthContext} from '../contexts/AuthContext';

export default function LoginPage() {
	const {login} = useContext(AuthContext);
	const [email, setEmail] = useState('');
	const [password, setPassword] = useState('');
	const [error, setError] = useState('');

	const handle = async e => {
		e.preventDefault();
		try {await login(email, password);}
		catch (error) {setError(error.message);}
	};

	return (
		<form onSubmit={handle}>
			<h2>Logowanie</h2>
			{error && <p>{error}</p>}

			<div class="login-form">
				<input value={email} onChange={e=>setEmail(e.target.value)} placeholder='Email' />
				<input type="password" value={password} onChange={e=>setPassword(e.target.value)} placeholder='Hasło' />
				<button type="submit">Zaloguj</button>
			</div>
		</form>
	);
}