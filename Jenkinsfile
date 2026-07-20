pipeline {
    agent none

    stages {
        // مرحله 1: کامپایل روی Agent اول
        stage('Build C++') {
            agent { label 'cpp-agent' }
            
            steps {
                checkout scm
                sh '''
                    set -e
                    mkdir -p build
                    g++ -std=c++20 *.cpp -Iinclude -o build/myapp
                '''
            }
            post {
                success {
                    stash name: 'built-app', includes: 'build/myapp, setup-server.yml, inventory'
                }
            }
        }

        // مرحله 2: دیپلوی با Ansible روی Agent دوم
        stage('Deploy with Ansible') {
            agent { label 'ansible-agent' }
            
            tools {
                ansible 'ansible'  // اسمی که تو Global Tool Configuration تنظیم کردی
            }
            
            steps {
                unstash 'built-app'
                
                // استفاده از پلاگین Ansible
              ansiblePlaybook(
    playbook: './setup-server.yml',
    inventory: './inventory',
    credentialsId: 'ansible-server',
    colorized: true,
    extras: "-v --ssh-extra-args='-o StrictHostKeyChecking=no'"
)            }
        }
    }
}
