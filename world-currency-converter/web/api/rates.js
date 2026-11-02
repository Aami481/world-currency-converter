export default async function handler(req, res) {
  const r = await fetch(`https://v6.exchangerate-api.com/v6/${process.env.RATES_KEY}/latest/USD`);
  const j = await r.json();
  const usd = {};
  for (const [k, v] of Object.entries(j.conversion_rates || {})) usd[k.toLowerCase()] = v;
  res.setHeader("Cache-Control", "s-maxage=3600");
  res.status(200).json({ date: new Date().toISOString().slice(0, 10), usd });
}
