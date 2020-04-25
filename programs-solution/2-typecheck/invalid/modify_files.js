const fs = require('fs');
const shelljs = require('shelljs');

let files = shelljs.ls();

files.forEach((file)=>{
	if(shelljs.test("-f",file)&& file.substring(file.indexOf(".go") !== -1)){
		let cont = fs.readFileSync(file).toString();
		console.log(file, cont);
		
		cont = cont.replace("var z =", "var z =");
		fs.writeFileSync(file, cont);
                console.log("After", cont);
	}
});


