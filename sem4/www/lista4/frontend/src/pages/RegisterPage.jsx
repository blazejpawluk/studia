import React, {useState, useContext} from 'react';
import {AuthContext} from '../contexts/AuthContext';

export default function RegisterPage() {
	const {register} = useContext(AuthContext);
	const [nickname, setNickname] = useState('');
	const [email, setEmail] = useState('');
	const [password, setPassword] = useState('');
	const [error, setError] = useState('');

	const handle = async e => {
		e.preventDefault();
		try {await register(nickname, email, password);}
		catch (error) {setError(error.message);}
	};

	return (
		<form onSubmit={handle}>
			<h2>Rejestracja</h2>
			{error && <p>{error}</p>}

			<div class="login-form">
				<input value={nickname} onChange={e=>setNickname(e.target.value)} placeholder='Nick' />
				<input value={email} onChange={e=>setEmail(e.target.value)} placeholder='Email' />
				<input type="password" value={password} onChange={e=>setPassword(e.target.value)} placeholder='Hasło' />
				<button type="submit">Zarejestruj</button>
			</div>
		</form>
	);
}