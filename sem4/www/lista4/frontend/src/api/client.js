const API_URL = '/api';

export async function apiRequest(path, {method='GET', body, auth} = {}) {
	const headers = {'Content-Type': 'application/json'};
	
	if (auth) {
		const token = localStorage.getItem('token');
		if (token) headers['Authorization'] = `Bearer ${token}`;
	}

	const res = await fetch(API_URL + path, {
		method,
		headers,
		body: body ? JSON.stringify(body) : undefined
	});

	const data = await res.json().catch(() => null);
	if (!res.ok) {
		const err = new Error(data?.message || res.statusText);
		err.status = res.status;
		throw err;
	} 
	return data;
}