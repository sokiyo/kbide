const gulp = require('gulp')
const path = require('path')
const fs = require('fs')
const download = require("gulp-download")
const del = require('del')
const exec = require('gulp-exec');

// build
const pathx = path.join(__dirname, '/xtensa-esp32-elf')
const patha = path.join(__dirname, '/app/package.json')
const pathc = path.join(__dirname, '/package.json')
const pathk = path.join(__dirname, '/archive/kidbright32.json')
const pathz = path.join(__dirname, '*.{tar,tar.bz2,tar.gz,zip}')
var pathl, pathe
var pathnl, pathne, pathnlt, pathnet

// clean
const pathca = path.join(__dirname, '/app/node_modules')
const pathcc = path.join(__dirname, '/node_modules')

gulp.task('install', () => {
    del([pathz])
    return gulp.src(__dirname).pipe(exec("npm install"))
        .pipe(exec("cd app && npm install"))
})

gulp.task('download_xtensa', ['install'], () => {
    var json = JSON.parse(fs.readFileSync(pathk))
    for (var i = 0; i < json.packages.length; i++) {
        if (process.platform === json.packages[i].platform) {
            pathl = json.packages[i].items[0].download_url
            pathnl = pathl.split("dl/")[1]
            pathnlt = pathnl.split('.gz')[0]
            console.log(pathnlt);
            pathe = json.packages[i].items[1].download_url
            if (process.platform === 'win32' || process.platform === 'darwin') {
                pathne = pathe.split("dl/")[1]
                pathnet = pathne.split('.gz')[0]
            }
            break
        }
    }
    if (fs.existsSync(pathx)) {
        return
    }
    else {
        return download(pathl)
            .pipe(gulp.dest(__dirname))
    }
})

gulp.task('download_esptool', ['download_xtensa'], () => {
    // if download url not defined
    if (pathe == '') {
        return;
    }

    return download(pathe)
            .pipe(gulp.dest(__dirname))
})

gulp.task('decompress', ['download_esptool'], () => {
    if (fs.existsSync(pathx)) {
        if (process.platform === 'darwin') {
            return gulp.src(__dirname)
                .pipe(exec('tar xvzf ' + pathne))
        } else if (process.platform === 'win32') {
            return gulp.src(__dirname)
                .pipe(exec("powershell.exe -NoP -NonI -Command " + "Expand-Archive '" + pathne + "' '.'"))
        }
        return
    } else {
        if (process.platform === 'darwin') {
            return gulp.src(__dirname)
                .pipe(exec('tar xvzf ' + pathnl))
                .pipe(exec('tar xvzf ' + pathne))
        } else if (process.platform === 'linux') {
            return gulp.src(__dirname)
                .pipe(exec('tar xvzf ' + pathnl))
        } else if (process.platform === 'win32') {
            return gulp.src(__dirname)
                .pipe(exec("powershell.exe -NoP -NonI -Command " + "Expand-Archive '" + pathnl + "' '.'"))
                .pipe(exec("powershell.exe -NoP -NonI -Command " + "Expand-Archive '" + pathne + "' '.'"))
        }
    }
})

gulp.task('chmod_linux', ['decompress'], () => {
    if (process.platform === 'linux') {
        return gulp.src(__dirname)
            .pipe(exec('chmod 755 esptool.py'))
    }
    else {
        return
    }
})

gulp.task('del', ['chmod_linux'], () => {
    return del([pathz])
})

gulp.task('build', ['del'], () => {
    return
})

gulp.task('clean', () => {
    return del([pathx, pathca, pathcc]).then(() => {
        
    })
})
